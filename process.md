kernel/fork.c
SYSCALL_DEFINE0(fork) -> kernel_clone() -> copy_process() ->dup_task_struct()
                                                          ->copy_flags()
                                                          ->alloc_pid()
                                                          

linux/kthread.h
kthread_create() + wake_up_process = kthread_run()

SYSCALL_DEFINE5(clone) -> kernel_clone()

kernel/exit.c
SYSCALL_DEFINE1(exit) -> do_exit()

release_task()

kernel/sched/core.c
schedule()



