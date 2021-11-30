kernel/fork.c

SYSCALL_DEFINE0(fork) -> kernel_clone() -> copy_process() ->dup_task_struct()

copy_process() ->alloc_pid()
                                                          

fs/exec.c

SYSCALL_DEFINE3(execve) -> do_execve() -> do_execveat_common()

kernel/exit.c

SYSCALL_DEFINE1(exit) -> do_exit()


SYSCALL_DEFINE4(wait4) -> kernel_wait4() -> do_wait() -> do_wait_pid()


kernel/sched/core.c

schedule() -> __schedule() -> context_switch()


linux/kthread.h

kthread_create() + wake_up_process = kthread_run()


SYSCALL_DEFINE5(clone) -> kernel_clone()


release_task()


Unserstanding the Linux Kernel
Chapter 20. Program ExZecution

* memory region layout

| Type of memory region                             | Classical layout                                                       | Flexible layout                                                                             |
| :-:                                               | :-:                                                                    | :-:                                                                                         |
| Text segment(ELF)                                 | Start from 0x08048000                                                  |                                                                                             |
| Data and bss segments                             | Start right after the text segment                                     |                                                                                             |
| Heap                                              | Start right after the data and bss segments                            |                                                                                             |
| File memory mappings and anonymous memory regions | Start from 0x40000000; libraries added as successively highter address | Starts near the end of the User Mode stack; libraries added at successively lower addresses |
| User Mode stack                                   | Starts at 0xc0000000 and grows towards lower addresses                 |                                                                                             |


The layouts differ only the position of the memory regions for file memory mappings and anonymous mappings.

[memorylayout.c](memorylayout.c)


