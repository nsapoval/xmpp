#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdarg.h>

#include "../lib/uthash.h"
#include "../lib/simclist.h"

typedef struct hh_pthread hh_pthread_t;
typedef struct thread_pool thread_pool_t;
typedef struct task_queue task_queue_t;

/*
 * A hashable instance of pthread_t
 */
typedef struct hh_pthread
{
    int id;
    pthread_t thread;

    thread_pool_t *parent_pool;

    UT_hash_handle hh;  // uthash.h for reference
} hh_pthread_t;

/*
 * Thread pool struct
 */
typedef struct thread_pool
{
    hh_pthread_t **thread_htable;  // hashatble of the threads in the pool

    volatile int num_idle_threads;  // number of idle threads in the pool
    pthread_mutex_t num_idle_threads_lock;

    task_queue_t *task_queue;
} thread_pool_t;

/*
 * Task queue for the thread pool
 */
typedef struct task_queue
{
    pthread_rwlock_t *task_queue_rwlock;
    list_t task_list;  // list of (task_t *)
} task_queue_t;

#endif