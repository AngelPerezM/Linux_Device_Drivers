The sleeping mechanism:
=======================

Sleeping is the mechanism by which a process stops using a processor, i.e., enters in the _sleeping_ mode and removed from the _run queue_. In this way, the processor can schedule other available processes.

The sleeping process can be inserted again into the run queue if its state changes (that is, it wakes up).

The Linux kernel provides the _wait queue (list)_ as a mechanism to put processes you want to sleep until a condition becomes true.

API overview:
-------------

### Static declaration:
```c
DECLARE_WAIT_QUEUE_HEAD(name)
```

### Dynamic declaration:
```c
init_wait_queue_head(wait_queue_head_t *wait_queue)
```

### Blocking:
```c
/* MACROS:
 * The difference between the two is that the process sleeping with interruptable
 * can be interrupted by any linux signal (e.g. SIGTERM). The _uninterruptable_
 * should be used for critical tasks.
 *
 * An interruptable task has the TASK_INTERRUPTABLE property and the
 * uninterruptable has the TASK_UNINTERRUPTABLE.
 */
int wait_event(wait_queue, CONDITION) 
int wait_event_interruptable(wait_queue, CONDITION)

int wait_event_timeout(wait_queue, CONDITION, timeout)
int wait_event_interruptable_timeout(wait_queue, CONDITION, timeout)

```

### Unblocking:
```c
/*
 * Wakes up only one process from the wait queue that is in uninterruptible sleep
 */
int wake_up(wait_queue_head_t *wait_queue)

/*
 * Wakes up only one process from the wait queue that is in interruptible sleep
 */
int wake_up_interruptable(wait_queue_head_t *wait_queue)
```
