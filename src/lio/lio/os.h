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

#ifndef ACCRE_LIO_OBJECT_SERVICE_ABSTRACT_H_INCLUDED
#define ACCRE_LIO_OBJECT_SERVICE_ABSTRACT_H_INCLUDED

#include <gop/gop.h>
#include <lio/authn.h>
#include <lio/visibility.h>
#include <lio/service_manager.h>
#include <regex.h>
#include <tbx/iniparse.h>

#ifdef __cplusplus
extern "C" {
#endif

// Typedefs
typedef struct object_service_fn_t object_service_fn_t;
typedef struct os_attr_tbx_list_t os_attr_tbx_list_t;
typedef struct os_authz_t os_authz_t;
typedef struct os_regex_entry_t os_regex_entry_t;
typedef struct os_regex_table_t os_regex_table_t;
typedef struct os_virtual_attr_t os_virtual_attr_t;
typedef void os_fd_t;
typedef void os_attr_iter_t;
typedef void os_object_iter_t;
typedef void os_fsck_iter_t;

typedef enum lio_object_type_t lio_object_type_t;
enum lio_object_type_t {
    OS_OBJECT_FILE        = 0,  //** File object or attribute
    OS_OBJECT_DIR         = 1,  //** Directory object
    OS_OBJECT_SYMLINK     = 2,  //** A symlinked object or attribute
    OS_OBJECT_HARDLINK    = 3,  //** A hard linked object
    OS_OBJECT_BROKEN_LINK = 4,  //** Signifies a broken link
    OS_OBJECT_VIRTUAL     = 5,  //** A virtual attribute
};

typedef enum lio_object_type_flag_t lio_object_type_flag_t;
enum lio_object_type_flag_t {
    OS_OBJECT_FILE_FLAG        = (1 << OS_OBJECT_FILE),
    OS_OBJECT_DIR_FLAG         = (1 << OS_OBJECT_DIR),
    OS_OBJECT_SYMLINK_FLAG     = (1 << OS_OBJECT_SYMLINK),
    OS_OBJECT_HARDLINK_FLAG    = (1 << OS_OBJECT_HARDLINK),
    OS_OBJECT_BROKEN_LINK_FLAG = (1 << OS_OBJECT_BROKEN_LINK),
    OS_OBJECT_VIRTUAL_FLAG     = (1 << OS_OBJECT_VIRTUAL),
    OS_OBJECT_ANY_FLAG         = (0x3F) // 6 bits AKA 0x3F,
};

typedef void (*lio_os_destroy_service_fn_t)(object_service_fn_t *os);
typedef os_fsck_iter_t *(*lio_os_create_fsck_iter_fn_t)(object_service_fn_t *os, creds_t *creds, char *path, int mode);
typedef void (*lio_os_destroy_fsck_iter_fn_t)(object_service_fn_t *os, os_fsck_iter_t *it);
typedef int (*lio_os_next_fsck_fn_t)(object_service_fn_t *os, os_fsck_iter_t *it, char **fname, int *ftype);
typedef op_generic_t *(*lio_os_fsck_object_fn_t)(object_service_fn_t *os, creds_t *creds, char *fname, int ftype, int resolution);
typedef creds_t *(*lio_os_cred_init_fn_t)(object_service_fn_t *os, int type, void **arg);
typedef void (*lio_os_cred_destroy_fn_t)(object_service_fn_t *os, creds_t *creds);
typedef op_generic_t *(*lio_os_exists_fn_t)(object_service_fn_t *os, creds_t *creds, char *path);
typedef op_generic_t *(*lio_os_create_object_fn_t)(object_service_fn_t *os, creds_t *creds, char *path, int type, char *id);
typedef op_generic_t *(*lio_os_remove_object_fn_t)(object_service_fn_t *os, creds_t *creds, char *path);
typedef op_generic_t *(*lio_os_remove_regex_object_fn_t)(object_service_fn_t *os, creds_t *creds, os_regex_table_t *path, os_regex_table_t *object_regex, int obj_types, int recurse_depth);
typedef op_generic_t *(*lio_os_abort_remove_regex_object_fn_t)(object_service_fn_t *os, op_generic_t *gop);
typedef op_generic_t *(*lio_os_regex_object_set_multiple_attrs_fn_t)(object_service_fn_t *os, creds_t *creds, char *id, os_regex_table_t *path, os_regex_table_t *object_regex, int object_types, int recurse_depth, char **key, void **val, int *v_size, int n);
typedef op_generic_t *(*lio_os_abort_regex_object_set_multiple_attrs_fn_t)(object_service_fn_t *os, op_generic_t *gop);
typedef op_generic_t *(*lio_os_move_object_fn_t)(object_service_fn_t *os, creds_t *creds, char *src_path, char *dest_path);
typedef op_generic_t *(*lio_os_symlink_object_fn_t)(object_service_fn_t *os, creds_t *creds, char *src_path, char *dest_path, char *id);
typedef op_generic_t *(*lio_os_hardlink_object_fn_t)(object_service_fn_t *os, creds_t *creds, char *src_path, char *dest_path, char *id);
typedef os_object_iter_t *(*lio_os_create_object_iter_fn_t)(object_service_fn_t *os, creds_t *creds, os_regex_table_t *path, os_regex_table_t *obj_regex, int object_types, os_regex_table_t *attr, int recurse_dpeth, os_attr_iter_t **it, int v_max);
typedef os_object_iter_t *(*lio_os_create_object_iter_alist_fn_t)(object_service_fn_t *os, creds_t *creds, os_regex_table_t *path, os_regex_table_t *obj_regex, int object_types, int recurse_depth, char **key, void **val, int *v_size, int n_keys);
typedef int (*lio_os_next_object_fn_t)(os_object_iter_t *it, char **fname, int *prefix_len);
typedef void (*lio_os_destroy_object_iter_fn_t)(os_object_iter_t *it);
typedef op_generic_t *(*lio_os_open_object_fn_t)(object_service_fn_t *os, creds_t *creds, char *path, int mode, char *id, os_fd_t **fd, int max_wait);
typedef op_generic_t *(*lio_os_close_object_fn_t)(object_service_fn_t *os, os_fd_t *fd);
typedef op_generic_t *(*lio_os_abort_open_object_fn_t)(object_service_fn_t *os, op_generic_t *gop);
typedef op_generic_t *(*lio_os_symlink_attr_fn_t)(object_service_fn_t *os, creds_t *creds, char *src_path, char *key_src, os_fd_t *fd_dest, char *key_dest);
typedef op_generic_t *(*lio_os_symlink_multiple_attrs_fn_t)(object_service_fn_t *os, creds_t *creds, char **src_path, char **key_src, os_fd_t *fd_dest, char **key_dest, int n);
typedef op_generic_t *(*lio_os_get_attr_fn_t)(object_service_fn_t *os, creds_t *creds, os_fd_t *fd, char *key, void **val, int *v_size);
typedef op_generic_t *(*lio_os_set_attr_fn_t)(object_service_fn_t *os, creds_t *creds, os_fd_t *fd, char *key, void *val, int v_size);
typedef op_generic_t *(*lio_os_move_attr_fn_t)(object_service_fn_t *os, creds_t *creds, os_fd_t *fd, char *key_old, char *key_new);
typedef op_generic_t *(*lio_os_copy_attr_fn_t)(object_service_fn_t *os, creds_t *creds, os_fd_t *fd_src, char *key_src, os_fd_t *fd_dest, char *key_dest);
typedef op_generic_t *(*lio_os_get_multiple_attrs_fn_t)(object_service_fn_t *os, creds_t *creds, os_fd_t *fd, char **key, void **val, int *v_size, int n);
typedef op_generic_t *(*lio_os_set_multiple_attrs_fn_t)(object_service_fn_t *os, creds_t *creds, os_fd_t *fd, char **key, void **val, int *v_size, int n);
typedef op_generic_t *(*lio_os_move_multiple_attrs_fn_t)(object_service_fn_t *os, creds_t *creds, os_fd_t *fd, char **key_old, char **key_new, int n);
typedef op_generic_t *(*lio_os_copy_multiple_attrs_fn_t)(object_service_fn_t *os, creds_t *creds, os_fd_t *fd_src, char **key_src, os_fd_t *fd_dest, char **key_dest, int n);
typedef os_attr_iter_t *(*lio_os_create_attr_iter_fn_t)(object_service_fn_t *os, creds_t *creds, os_fd_t *fd, os_regex_table_t *attr, int v_max);
typedef int (*lio_os_next_attr_fn_t)(os_attr_iter_t *it, char **key, void **val, int *v_size);
typedef int (*lio_os_add_virtual_attr_fn_t)(os_virtual_attr_t *va, char *key, int type);
typedef void (*lio_os_destroy_attr_iter_fn_t)(os_attr_iter_t *it);

//* FIXME: leaky
typedef struct osfile_priv_t osfile_priv_t;
typedef struct local_object_iter_t local_object_iter_t;
typedef struct osrc_priv_t osrc_priv_t;
typedef struct osrs_priv_t osrs_priv_t;

// Functions
LIO_API char *lio_os_glob2regex(char *glob);
LIO_API int lio_os_local_filetype(char *path);
LIO_API os_regex_table_t *lio_os_path_glob2regex(char *path);
LIO_API void lio_os_path_split(const char *path, char **dir, char **file);
LIO_API os_regex_table_t *lio_os_regex2table(char *regex);
LIO_API int lio_os_regex_is_fixed(os_regex_table_t *regex);
LIO_API void lio_os_regex_table_destroy(os_regex_table_t *table);

// Preprocessor constants
#define OS_PATH_MAX  32768    //** Max path length


#define OS_FSCK_MANUAL    0   //** Manual resolution via fsck_resolve() or user control
#define OS_FSCK_REMOVE    1   //** Removes the problem object
#define OS_FSCK_REPAIR    2   //** Repairs the problem object

#define OS_FSCK_GOOD            0 //** Nothing wrong with the object
#define OS_FSCK_MISSING_ATTR    1 //** Missing the object attributes
#define OS_FSCK_MISSING_OBJECT  2 //** Missing file entry

#define OS_FSCK_FINISHED  0   //** FSCK scan is finished
#define OS_FSCK_ERROR    -1   //** FSCK internal error

#define OS_MODE_READ_IMMEDIATE  0

// Preprocessor macros
#define os_close_object(os, fd) (os)->close_object(os, fd)
#define os_create_fsck_iter(os, c, path, mode) (os)->create_fsck_iter(os, c, path, mode)
#define os_destroy_fsck_iter(os, it) (os)->destroy_fsck_iter(os, it)
#define os_fsck_object(os, c, fname, ftype, mode) (os)->fsck_object(os, c, fname, ftype, mode)
#define os_next_fsck(os, it, fname, atype) (os)->next_fsck(os, it, fname, atype)
#define os_open_object(os, c, path, mode, id, fd, max_wait) (os)->open_object(os, c, path, mode, id, fd, max_wait)
#define os_symlink_multiple_attrs(os, c, src_path, key_src, fd_dest, key_dest, n) (os)->symlink_multiple_attrs(os, c, src_path, key_src, fd_dest, key_dest, n)

// Exported types. To be obscured
struct object_service_fn_t {
    void *priv;
    char *type;
    lio_os_destroy_service_fn_t destroy_service;
    lio_os_create_fsck_iter_fn_t create_fsck_iter;
    lio_os_destroy_fsck_iter_fn_t destroy_fsck_iter;
    lio_os_next_fsck_fn_t next_fsck;
    lio_os_fsck_object_fn_t fsck_object;
    lio_os_cred_init_fn_t cred_init;
    lio_os_cred_destroy_fn_t cred_destroy;
    lio_os_exists_fn_t exists;
    lio_os_create_object_fn_t create_object;
    lio_os_remove_object_fn_t remove_object;
    lio_os_remove_regex_object_fn_t remove_regex_object;
    lio_os_abort_remove_regex_object_fn_t abort_remove_regex_object;
    lio_os_regex_object_set_multiple_attrs_fn_t regex_object_set_multiple_attrs;
    lio_os_abort_regex_object_set_multiple_attrs_fn_t abort_regex_object_set_multiple_attrs;
    lio_os_move_object_fn_t move_object;
    lio_os_symlink_object_fn_t symlink_object;
    lio_os_hardlink_object_fn_t hardlink_object;
    lio_os_create_object_iter_fn_t create_object_iter;
    lio_os_create_object_iter_alist_fn_t create_object_iter_alist;
    lio_os_next_object_fn_t next_object;
    lio_os_destroy_object_iter_fn_t destroy_object_iter;
    lio_os_open_object_fn_t open_object;
    lio_os_close_object_fn_t close_object;
    lio_os_abort_open_object_fn_t abort_open_object;
    lio_os_symlink_attr_fn_t symlink_attr;
    lio_os_symlink_multiple_attrs_fn_t symlink_multiple_attrs;
    lio_os_get_attr_fn_t get_attr;
    lio_os_set_attr_fn_t set_attr;
    lio_os_move_attr_fn_t move_attr;
    lio_os_copy_attr_fn_t copy_attr;
    lio_os_get_multiple_attrs_fn_t get_multiple_attrs;
    lio_os_set_multiple_attrs_fn_t set_multiple_attrs;
    lio_os_move_multiple_attrs_fn_t move_multiple_attrs;
    lio_os_copy_multiple_attrs_fn_t copy_multiple_attrs;
    lio_os_create_attr_iter_fn_t create_attr_iter;
    lio_os_next_attr_fn_t next_attr;
    lio_os_add_virtual_attr_fn_t add_virtual_attr;
    lio_os_destroy_attr_iter_fn_t destroy_attr_iter;
};

struct os_regex_entry_t {
    char *expression;
    int fixed;
    int fixed_prefix;
    regex_t compiled;
};

struct os_regex_table_t {
    int n;
    os_regex_entry_t *regex_entry;
};
#ifdef __cplusplus
}
#endif

#endif /* ^ ACCRE_LIO_OBJECT_SERVICE_ABSTRACT_H_INCLUDED ^ */ 