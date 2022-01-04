## Pipes and FIFOs(named pipes)

SYSCALL_DEFINE2(pipe2) -> do_pipe2() -> __do_pipe_flags() -> create_pipe_files()

### FIFOs

There is no way to open an already existing pipes. An opened FIFO is associated with a kernel buffer that temporarily sotres the data exchanged by two or more processes.

* FIFO inodes appear on the system directory tree rather than on the pipefs special filesystem.

* FIFOs are a bidirectional communication channel; that is, it is possible to open a FIFO in read/write mode.

## System V IPC

* synchronize by semaphores
 
* send messages

* share a memory area

IPC resource(a semaphore, a message queue, or a shared memory region)

* An IPC resource is persistent; unless explicitly removed by a preocess, it is kept in memory and remains available until the system is shut down. An IPC resource may be used by every process, including those that do not share the ancestor that created the resource.

### Semaphores

### Messages

### Shared memory regions

## Sockets

## POSIX Message Queues

* simpler file-based interface to the applications

* native support for message priorities

* native support for asynchronous notification of message arrivals

* timeouts for blocking send and receive operations


