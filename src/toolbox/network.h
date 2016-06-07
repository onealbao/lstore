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

//*************************************************************************
//*************************************************************************

#ifndef __NETWORK_H_
#define __NETWORK_H_

#define N_BUFSIZE  1024

#include "tbx/toolbox_visibility.h"
#include <apr_network_io.h>
#include <apr_thread_proc.h>
#include <apr_thread_mutex.h>
#include <apr_thread_cond.h>
#include <apr_pools.h>
#include <string.h>
#include "tbx/transfer_buffer.h"
#include "tbx/chksum.h"
// Private interfaces
#include "chksum.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NETWORK_MON_MAX 10   //** Max number of ports allowed to monitor

//** Return values for write_netstream_block **
#define NS_OK       0   //** Command completed without errors
#define NS_TIMEOUT -1   //** Didn't complete in given time
#define NS_SOCKET  -2   //** Socket error
#define NS_CHKSUM  -3   //** Chksum error

#define NS_STATE_DISCONNECTED  0   //NetStream is disconnected
#define NS_STATE_CONNECTED     1   //NS is connected with no ongoing transaction
#define NS_STATE_ONGOING_READ  2   //NS is connected and has partially processed a command (in read state)
#define NS_STATE_ONGOING_WRITE 3   //NS is connected and has partially processed a command (in write state)
#define NS_STATE_READ_WRITE    4   //NS is connected and doing both Rread and write operations
#define NS_STATE_IGNORE        5   //NS is connected but is in a holding pattern so don't monitor it for traffic

typedef int ns_native_fd_t;

typedef void net_sock_t;

struct ns_monitor_s;   //** Forward declaration

struct tbx_ns_chksum_t {  //** NetStream checksum container
    int64_t blocksize;   //** Checksum block size or how often to inject/extract the checksum information
    int64_t bytesleft;       //** Current byte count until a full block
    int    is_running;  //** Current state.  1=running
    int    is_valid;     //** Has a valid chksum stored
    tbx_chksum_t chksum;    //** Checksum to use
};

struct tbx_ns_t {
    int id;                  //ID for tracking purposes
    int cuid;                //Unique ID for the connection.  Changes each time the connection is open/closed
    int start;               //Starting position of buffer data
    int end;                 //End position of buffer data
    int sock_type;           //Socket type
    net_sock_t *sock;        //Private socket data.  Depends on socket type
    apr_time_t last_read;        //Last time this connection was used
    apr_time_t last_write;        //Last time this connection was used
    char buffer[N_BUFSIZE];  //intermediate buffer for the conection
    apr_pool_t *mpool;       //** Memory pool for the connection (workaround since APR pools aren't thread safe)
    apr_thread_mutex_t *read_lock;    //Read lock
    apr_thread_mutex_t *write_lock;   //Write lock
    char peer_address[128];
    struct ns_monitor_s *nm;      //This is only used for an accept call to tell which bind was accepted
    tbx_ns_chksum_t read_chksum;      //Read chksum
    tbx_ns_chksum_t write_chksum;     //Write chksum
    ns_native_fd_t (*native_fd)(net_sock_t *sock);  //** Native socket if supported
    int (*close)(net_sock_t *sock);  //** Close socket
    long int (*write)(net_sock_t *sock, tbx_tbuf_t *buf, size_t boff, size_t count, tbx_ns_timeout_t tm);
    long int (*read)(net_sock_t *sock, tbx_tbuf_t *buf, size_t boff, size_t count, tbx_ns_timeout_t tm);
    void (*set_peer)(net_sock_t *sock, char *address, int add_size);
    int (*sock_status)(net_sock_t *sock);
    int (*connect)(net_sock_t *sock, const char *hostname, int port, tbx_ns_timeout_t timeout);
    net_sock_t *(*accept)(net_sock_t *sock);
    int (*bind)(net_sock_t *sock, char *address, int port);
    int (*listen)(net_sock_t *sock, int max_pending);
    int (*connection_request)(net_sock_t *sock, int timeout);
};

struct tbx_ns_monitor_t {   //** Struct used to handle ports being monitored
    tbx_ns_t *ns;       //** Connection actually being monitored
    char *address;         //** Interface to bind to
    int port;              //** Port to use
    int is_pending;        //** Flags the connections as ready for an accept call
    int shutdown_request;  //** Flags the connection to shutdown
    apr_thread_t *thread;  //** Execution thread handle
    apr_pool_t *mpool;     //** Memory pool for the thread
    apr_thread_mutex_t *lock;  //** Lock used for blocking pending accept
    apr_thread_cond_t *cond;   //** cond used for blocking pending accept
    apr_thread_mutex_t *trigger_lock; //** Lock used for sending globabl pending trigger
    apr_thread_cond_t *trigger_cond;   //** cond used for sending globabl pending accept
    int *trigger_count;             //** Gloabl count of pending requests
};

struct tbx_network_t {
    int accept_pending;      //New connection is pending
    int used_ports;          //Number of monitor ports used
    int monitor_index;       //Last ns checked in accept polling
    tbx_ns_monitor_t nm[NETWORK_MON_MAX];  //List of ports being monitored
    apr_pool_t *mpool;       //** Memory pool
    apr_thread_mutex_t *ns_lock; //Lock for serializing ns modifications
    apr_thread_cond_t *cond;   //** cond used for blocking pending accept
};

#define ns_native_fd(ns) (ns)->native_fd((ns)->sock)
#define ns_native_enabled(ns) (ns)->native_fd
#define ns_get_type(ns) (ns)->sock_type
#define ns_get_monitor(ns) ns->nm
#define nm_get_port(nm) nm->port
#define nm_get_host(nm) nm->address


#define ns_chksum_disable(ncs)  (ncs)->is_running = 0
//#define tbx_ns_chksum_is_valid(ncs) (ncs)->is_valid

//#define ns_read_tbx_chksum_reset(ns)  tbx_ns_chksum_reset(&((ns)->read_chksum))
#define ns_read_chksum_bytesleft(ns) (ns)->read_chksum.bytesleft
#define ns_read_chksum_state(ns)  (ns)->read_chksum.is_running

#define ns_write_chksum_bytesleft(ns) (ns)->write_chksum.bytesleft
#define ns_write_chksum_state(ns)  (ns)->write_chksum.is_running

void set_network_tcpsize(int tcpsize);
int get_network_tcpsize(int tcpsize);
int ns_merge_ssl(tbx_ns_t *ns1, tbx_ns_t *ns2);
int ns_socket2ssl(tbx_ns_t *ns);
void set_ns_slave(tbx_ns_t *ns, int slave);
int connection_is_pending(tbx_network_t *net);
int wait_for_connection(tbx_network_t *net, int max_wait);
void lock_ns(tbx_ns_t *ns);
void unlock_ns(tbx_ns_t *ns);
int bind_server_port(tbx_network_t *net, tbx_ns_t *ns, char *address, int port, int max_pending);
tbx_network_t *network_init();
void network_close(tbx_network_t *net);
void network_destroy(tbx_network_t *net);
int sniff_connection(tbx_ns_t *ns);
int write_netstream_block(tbx_ns_t *ns, apr_time_t end_time, tbx_tbuf_t *buffer, unsigned int boff, int bsize);
int read_netstream_block(tbx_ns_t *ns, apr_time_t end_time, tbx_tbuf_t *buffer, unsigned int boff, int bsize);
int readline_netstream(tbx_ns_t *ns, tbx_tbuf_t *buffer, unsigned int boff, int bsize, tbx_ns_timeout_t timeout);
int accept_pending_connection(tbx_network_t *net, tbx_ns_t *ns);
void get_net_timeout(tbx_ns_timeout_t tm, int *sec, int *us);
void ns_init(tbx_ns_t *ns);
void _ns_init(tbx_ns_t *ns, int incid);
void wakeup_network(tbx_network_t *net);

#ifdef __cplusplus
}
#endif

#endif



