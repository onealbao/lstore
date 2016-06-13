/*
   Copyright 2016 Vanderbilt University

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef ACCRE_GOP_H_INCLUDED
#define ACCRE_GOP_H_INCLUDED

#include "gop/gop_visibility.h"
#include <apr_thread_mutex.h>
#include <apr_thread_cond.h>
#include <apr_hash.h>
#include <tbx/atomic_counter.h>
#include <tbx/network.h>
#include <tbx/stack.h>
#include "callback.h"
#include <tbx/pigeon_coop.h>
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

// Types
struct gop_control_t {
    apr_thread_mutex_t *lock;  //** shared lock
    apr_thread_cond_t *cond;   //** shared condition variable
    tbx_pch_t  pch;   //** Pigeon coop hole for the lock and cond
};

struct op_status_t {       //** Generic opcode status
    int op_status;          //** Simplified operation status, OP_SUCCESS or OP_FAILURE
    int error_code;         //** Low level op error code
};

struct command_op_t {   //** Command operation
    char *hostport; //** Depot hostname:port:type:...  Unique string for host/connect_context
    void *connect_context;   //** Private information needed to make a host connection
    int  cmp_size;  //** Used for ordering commands within the same host
    apr_time_t timeout;    //** Command timeout
    apr_time_t retry_wait; //** How long to wait in case of a dead socket, if 0 then retry immediately
    int64_t workload;   //** Workload for measuring channel usage
    int retry_count;//** Number of times retried
    op_status_t (*send_command)(op_generic_t *gop, tbx_ns_t *ns);  //**Send command routine
    op_status_t (*send_phase)(op_generic_t *gop, tbx_ns_t *ns);    //**Handle "sending" side of command
    op_status_t (*recv_phase)(op_generic_t *gop, tbx_ns_t *ns);    //**Handle "receiving" half of command
    int (*on_submit)(tbx_stack_t *stack, tbx_stack_ele_t *gop_ele);                      //** Executed during initial execution submission
    int (*before_exec)(op_generic_t *gop);                    //** Executed when popped off the globabl que
    int (*destroy_command)(op_generic_t *gop);                //**Destroys the data structure
    tbx_stack_t  *coalesced_ops;                                  //** Stores any other coalesced ops
    tbx_atomic_unit32_t on_top;
    apr_time_t start_time;
    apr_time_t end_time;
};

struct op_common_t {
    callback_t *cb;        //** Optional callback
    opque_t *parent_q;     //** Parent que attached to
    op_status_t status;    //** Command result
    int failure_mode;      //** Used via the callbacks to force a failure, even on success
    int retries;           //** Upon failure how many times we've retried
    int id;                //** Op's global id.  Can be changed by use but generally should use my_id
    int my_id;             //** User/Application settable id.  Defaults to id.
    int state;             //** Command state 0=submitted 1=completed
    int started_execution; //** If 1 the tasks have already been submitted for execution
    int execution_mode;    //** Execution mode OP_EXEC_QUEUE | OP_EXEC_DIRECT
    int auto_destroy;      //** If 1 then automatically call the free fn to destroy the object
    gop_control_t *ctl;    //** Lock and condition struct
    void *user_priv;           //** Optional user supplied handle
    void (*free)(op_generic_t *d, int mode);
    portal_context_t *pc;
};

struct op_data_t {
    portal_context_t *pc;
    command_op_t cmd;
    void *priv;
};

struct op_generic_t {
    int type;
    void *free_ptr;
    op_common_t base;
    que_data_t   *q;
    op_data_t   *op;
};


#define OP_STATE_SUCCESS  10
#define OP_STATE_FAILURE  20
#define OP_STATE_RETRY    30
#define OP_STATE_DEAD     40
#define OP_STATE_TIMEOUT  50
#define OP_STATE_INVALID_HOST 60
#define OP_STATE_CANT_CONNECT 70
#define OP_STATE_ERROR    80

#define Q_TYPE_OPERATION 50
#define Q_TYPE_QUE       51

#define OP_FINALIZE      -10
#define OP_DESTROY       -20

#define OP_FM_FORCED     11
#define OP_FM_GET_END    22

#define OP_EXEC_QUEUE    100
#define OP_EXEC_DIRECT   101

GOP_API extern op_status_t op_success_status;
GOP_API extern op_status_t op_failure_status;
extern op_status_t op_retry_status;
extern op_status_t op_dead_status;
extern op_status_t op_timeout_status;
extern op_status_t op_invalid_host_status;
extern op_status_t op_cant_connect_status;
GOP_API extern op_status_t op_error_status;


extern tbx_atomic_unit32_t _opque_counter;

#define _op_set_status(v, opstat, errcode) (v).op_status = opstat; (v).error_code = errcode

#define lock_gop(gop)   log_printf(15, "lock_gop: gid=%d\n", (gop)->base.id); apr_thread_mutex_lock((gop)->base.ctl->lock)
#define unlock_gop(gop) log_printf(15, "unlock_gop: gid=%d\n", (gop)->base.id); apr_thread_mutex_unlock((gop)->base.ctl->lock)
#define gop_id(gop) (gop)->base.id
#define gop_get_auto_destroy(gop) (gop)->base.auto_destroy
#define gop_get_private(gop) (gop)->base.user_priv
#define gop_set_private(gop, newval) (gop)->base.user_priv = newval
#define gop_get_id(gop) (gop)->base.id
#define gop_set_id(gop, newval) (gop)->base.id = newval
#define gop_get_myid(gop) (gop)->base.my_id
#define gop_set_myid(gop, newval) (gop)->base.my_id = newval
#define gop_get_type(gop) (gop)->type
#define gop_get_status(gop) (gop)->base.status
#define gop_set_status(gop, val) (gop)->base.status = val

void gop_simple_cb(void *v, int mode);

GOP_API op_generic_t *gop_dummy(op_status_t state);
GOP_API void gop_free(op_generic_t *gop, int mode);
GOP_API void gop_set_auto_destroy(op_generic_t *gop, int val);
void gop_set_success_state(op_generic_t *g, op_status_t state);
GOP_API void gop_callback_append(op_generic_t *q, callback_t *cb);
GOP_API op_generic_t *gop_get_next_finished(op_generic_t *gop);
GOP_API op_generic_t *gop_get_next_failed(op_generic_t *gop);
GOP_API int gop_tasks_failed(op_generic_t *gop);
GOP_API int gop_tasks_finished(op_generic_t *gop);
GOP_API int gop_tasks_left(op_generic_t *gop);
int gop_will_block(op_generic_t *g);
GOP_API int gop_waitall(op_generic_t *gop);
GOP_API op_generic_t *gop_waitany(op_generic_t *gop);
GOP_API op_generic_t *gop_timed_waitany(op_generic_t *g, int dt);
int gop_timed_waitall(op_generic_t *g, int dt);
GOP_API void gop_start_execution(op_generic_t *gop);
GOP_API void gop_finished_submission(op_generic_t *gop);
GOP_API void gop_set_exec_mode(op_generic_t *g, int mode);

GOP_API int gop_completed_successfully(op_generic_t *gop);

void gop_mark_completed(op_generic_t *gop, op_status_t status);
GOP_API int gop_sync_exec(op_generic_t *gop);
GOP_API op_status_t gop_sync_exec_status(op_generic_t *gop);
GOP_API void gop_reset(op_generic_t *gop);
GOP_API void gop_init(op_generic_t *gop);
GOP_API void gop_generic_free(op_generic_t *gop, int mode);
void gop_callback_append(op_generic_t *gop, callback_t *cb);
GOP_API apr_time_t gop_exec_time(op_generic_t *gop);
apr_time_t gop_start_time(op_generic_t *gop);
apr_time_t gop_end_time(op_generic_t *gop);

#ifdef __cplusplus
}
#endif


#endif
