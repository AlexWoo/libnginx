
/*
 * Copyright (C) Igor Sysoev
 * Copyright (C) Nginx, Inc.
 */


#ifndef _NGX_CORE_H_INCLUDED_
#define _NGX_CORE_H_INCLUDED_


#include <ngx_config.h>

typedef int                      ngx_err_t;
typedef int                      ngx_fd_t;
typedef uid_t                    ngx_uid_t;
typedef pid_t                    ngx_pid_t;

typedef ngx_uint_t               ngx_rbtree_key_t;
typedef ngx_int_t                ngx_rbtree_key_int_t;
typedef ngx_rbtree_key_t         ngx_msec_t;
typedef ngx_rbtree_key_int_t     ngx_msec_int_t;

typedef struct stat              ngx_file_info_t;

typedef int64_t                  ngx_atomic_int_t;
typedef uint64_t                 ngx_atomic_uint_t;
typedef volatile ngx_atomic_uint_t  ngx_atomic_t;

#define NGX_ATOMIC_T_LEN            (sizeof("-9223372036854775808") - 1)

typedef struct ngx_pool_s        ngx_pool_t;
typedef struct ngx_chain_s       ngx_chain_t;
typedef struct ngx_log_s         ngx_log_t;
typedef struct ngx_file_s        ngx_file_t;

#if (NGX_THREADS)
typedef struct ngx_thread_task_s  ngx_thread_task_t;
#endif


#define  NGX_OK          0
#define  NGX_ERROR      -1
#define  NGX_AGAIN      -2
#define  NGX_BUSY       -3
#define  NGX_DONE       -4
#define  NGX_DECLINED   -5
#define  NGX_ABORT      -6


#include <ngx_rbtree.h>
#include <ngx_string.h>
#include <ngx_palloc.h>
#include <ngx_buf.h>
#include <ngx_queue.h>
#include <ngx_array.h>
#include <ngx_list.h>
#include <ngx_hash.h>
#include <ngx_radix_tree.h>
#include <ngx_alloc.h>


#define LF     (u_char) '\n'
#define CR     (u_char) '\r'
#define CRLF   "\r\n"


#define ngx_abs(value)       (((value) >= 0) ? (value) : - (value))
#define ngx_max(val1, val2)  ((val1 < val2) ? (val2) : (val1))
#define ngx_min(val1, val2)  ((val1 > val2) ? (val2) : (val1))

void ngx_cpuinfo(void);

#if (NGX_HAVE_OPENAT)
#define NGX_DISABLE_SYMLINKS_OFF        0
#define NGX_DISABLE_SYMLINKS_ON         1
#define NGX_DISABLE_SYMLINKS_NOTOWNER   2
#endif

#define NGX_INVALID_FILE         -1
#define NGX_FILE_ERROR           -1

#define ngx_close_file           close
#define ngx_close_file_n         "close()"

#define ngx_delete_file(name)    unlink((const char *) name)
#define ngx_delete_file_n        "unlink()"

#define NGX_LOG_EMERG             1
#define NGX_LOG_ALERT             2
#define NGX_LOG_CRIT              3
#define NGX_LOG_ERR               4
#define NGX_LOG_WARN              5
#define NGX_LOG_NOTICE            6
#define NGX_LOG_INFO              7
#define NGX_LOG_DEBUG             8

#define ngx_log_error(level, log, ...)
#define ngx_log_debug(level, log, args...)

#define ngx_log_debug0(level, log, err, fmt)                                  \
        ngx_log_debug(level, log, err, fmt)

#define ngx_log_debug1(level, log, err, fmt, arg1)                            \
        ngx_log_debug(level, log, err, fmt, arg1)

#define ngx_log_debug2(level, log, err, fmt, arg1, arg2)                      \
        ngx_log_debug(level, log, err, fmt, arg1, arg2)

#define ngx_log_debug3(level, log, err, fmt, arg1, arg2, arg3)                \
        ngx_log_debug(level, log, err, fmt, arg1, arg2, arg3)

#define ngx_log_debug4(level, log, err, fmt, arg1, arg2, arg3, arg4)          \
        ngx_log_debug(level, log, err, fmt, arg1, arg2, arg3, arg4)

#define ngx_log_debug5(level, log, err, fmt, arg1, arg2, arg3, arg4, arg5)    \
        ngx_log_debug(level, log, err, fmt, arg1, arg2, arg3, arg4, arg5)

#define ngx_log_debug6(level, log, err, fmt,                                  \
                       arg1, arg2, arg3, arg4, arg5, arg6)                    \
        ngx_log_debug(level, log, err, fmt,                                   \
                       arg1, arg2, arg3, arg4, arg5, arg6)

#define ngx_log_debug7(level, log, err, fmt,                                  \
                       arg1, arg2, arg3, arg4, arg5, arg6, arg7)              \
        ngx_log_debug(level, log, err, fmt,                                   \
                       arg1, arg2, arg3, arg4, arg5, arg6, arg7)

#define ngx_log_debug8(level, log, err, fmt,                                  \
                       arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)        \
        ngx_log_debug(level, log, err, fmt,                                   \
                       arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8)

#define NGX_EPERM         EPERM
#define NGX_ENOENT        ENOENT
#define NGX_ENOPATH       ENOENT
#define NGX_ESRCH         ESRCH
#define NGX_EINTR         EINTR
#define NGX_ECHILD        ECHILD
#define NGX_ENOMEM        ENOMEM
#define NGX_EACCES        EACCES
#define NGX_EBUSY         EBUSY
#define NGX_EEXIST        EEXIST
#define NGX_EEXIST_FILE   EEXIST
#define NGX_EXDEV         EXDEV
#define NGX_ENOTDIR       ENOTDIR
#define NGX_EISDIR        EISDIR
#define NGX_EINVAL        EINVAL
#define NGX_ENFILE        ENFILE
#define NGX_EMFILE        EMFILE
#define NGX_ENOSPC        ENOSPC
#define NGX_EPIPE         EPIPE
#define NGX_EINPROGRESS   EINPROGRESS
#define NGX_ENOPROTOOPT   ENOPROTOOPT
#define NGX_EOPNOTSUPP    EOPNOTSUPP
#define NGX_EADDRINUSE    EADDRINUSE
#define NGX_ECONNABORTED  ECONNABORTED
#define NGX_ECONNRESET    ECONNRESET
#define NGX_ENOTCONN      ENOTCONN
#define NGX_ETIMEDOUT     ETIMEDOUT
#define NGX_ECONNREFUSED  ECONNREFUSED
#define NGX_ENAMETOOLONG  ENAMETOOLONG
#define NGX_ENETDOWN      ENETDOWN
#define NGX_ENETUNREACH   ENETUNREACH
#define NGX_EHOSTDOWN     EHOSTDOWN
#define NGX_EHOSTUNREACH  EHOSTUNREACH
#define NGX_ENOSYS        ENOSYS
#define NGX_ECANCELED     ECANCELED
#define NGX_EILSEQ        EILSEQ
#define NGX_ENOMOREFILES  0
#define NGX_ELOOP         ELOOP
#define NGX_EBADF         EBADF

#if (NGX_HAVE_OPENAT)
#define NGX_EMLINK        EMLINK
#endif

#if (__hpux__)
#define NGX_EAGAIN        EWOULDBLOCK
#else
#define NGX_EAGAIN        EAGAIN
#endif


#define ngx_errno                  errno


struct ngx_file_s {
    ngx_fd_t                   fd;
    ngx_str_t                  name;
    ngx_file_info_t            info;

    off_t                      offset;
    off_t                      sys_offset;

    ngx_log_t                 *log;

    unsigned                   valid_info:1;
    unsigned                   directio:1;
};

#endif /* _NGX_CORE_H_INCLUDED_ */
