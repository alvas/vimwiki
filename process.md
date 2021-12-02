kernel/fork.c

SYSCALL_DEFINE0(fork) -> kernel_clone() -> copy_process() ->dup_task_struct()

copy_process() ->alloc_pid()
                                                          

SYSCALL_DEFINE5(clone) -> kernel_clone()


fs/exec.c

SYSCALL_DEFINE3(execve) -> do_execve() -> do_execveat_common()

kernel/exit.c

SYSCALL_DEFINE1(exit) -> do_exit()


SYSCALL_DEFINE4(wait4) -> kernel_wait4() -> do_wait() -> do_wait_pid()


kernel/sched/core.c

schedule() -> __schedule() -> context_switch()


linux/kthread.h

kthread_create() + wake_up_process = kthread_run()


release_task()


