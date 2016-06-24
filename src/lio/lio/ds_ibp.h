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

/** \file
* Autogenerated public API
*/

#ifndef ACCRE_LIO_DS_IBP_H_INCLUDED
#define ACCRE_LIO_DS_IBP_H_INCLUDED

#include <apr_hash.h>
#include <apr_thread_cond.h>
#include <apr_thread_proc.h>
#include <lio/lio_visibility.h>

#ifdef __cplusplus
extern "C" {
#endif

// Typedefs
typedef struct ds_ibp_attr_t ds_ibp_attr_t;
typedef struct ds_ibp_alloc_op_t ds_ibp_alloc_op_t;
typedef struct ds_ibp_op_t ds_ibp_op_t;
typedef struct ds_ibp_priv_t ds_ibp_priv_t;
typedef struct ds_ibp_truncate_op_t ds_ibp_truncate_op_t;

// Functions

// Exported types. To be obscured
struct ds_ibp_attr_t {
    ibp_attributes_t attr;
    ibp_depot_t depot;
    ibp_connect_context_t cc;
    tbx_ns_chksum_t ncs;
    int disk_cs_type;
    int disk_cs_blocksize;
};

struct ds_ibp_priv_t {
    ds_ibp_attr_t attr_default;
    ibp_context_t *ic;

    //** These are all for the warmer
    apr_pool_t *pool;
    apr_hash_t *warm_table;
    apr_thread_mutex_t *lock;
    apr_thread_cond_t *cond;
    apr_thread_t *thread;
    int warm_interval;
    int warm_duration;
    int warm_stop;
};
#ifdef __cplusplus
}
#endif

#endif /* ^ ACCRE_LIO_DS_IBP_H_INCLUDED ^ */ 
