# The Virtual Filesystem

Five standard Unix file types: regular files, directories, symbolic links, device files and pipes

The Virtual Filesystem is a kernel software layer that handles all system calls related to a standard Unix filesystem. 

Filesystems  supported by the VFS may be grouped into three main classes:
* Disk-based filesystems
* Network filesystems
* Special filesystems

The root directory is contained in the root filesystem, which in Linux, is usually of type Ext2 or Ext3. All other filesystems can be "mounted" on subdirectories of the root filesystem. A useful feature of Linux's VFS allows it to handle virtual block devices such as /dev/loop0, which may be used to mount filesystems stored in regular files. 


The common file model consists of the following object types:

* The superblock object
Stores information concerning a mounted filesystem. For disk-based filesystems, this object usually corresponds to a filesystem control block stored on disk.

super_block{},


* The inode object
Stores general information about a specific file. For disk-based filesystems, this object usually corresponds to a file control block stored on disk. Each inode{} object is associated with an inode number, which uniquely identifies the file within the filesystem.

All information needed by the filesystem to handle a file is included in a data structure called an inode.

Each inode object duplicates some of the data included in the disk inode.


* The file object
Stores information about the interaction between an open file and a process. This information exists only in kernel memory during the period when a process has the file open.

A file object describes how a process interacts with a file it has opened. The object is created when the file is opened and consists of a file{} structure. File objects have no corresponding image on disk, and hence no "dirty" field is included in the file{} structure to specify that the file object has been modified.

The main information stored in a file object is the file pointer -- the current position in the file from which the next operation will take place. 

* The dentry object
Once a directory entry is read into memory, it is transformed by the VFS into a dentry object based on the dentry structure. The kernel creates a dentry object for every component of a pathname that a process looks up; the dentry object associates the component to its corresponding inode. Notice that dentry objects has no corresponding image on disk, and hence no field is included in the dentry structure to specify that the object has been modified.

Stores information about the linking of a directory entry(a particular name of the file) with the corresponding file. Each disk-based filesystem stores this information in its own particular way on disk.

The most recently used dentry objects are contained in a disk cache named the dentry cache, which speeds up the translation from a file pathname to the inode of the last pathname component. A disk cache is a software mechanism that allows the kernel to keep in RAM some information that is normally stored on a disk, so that further accesses to that data can be quickly satisfied without a slow access to the disk itself.

Disk cache is different from hardware cache or memory cache. A hardware cache is a fast static RAM that speeds up requests directed to the slower dynamic RAM. A memory cache is a software mechanism introduced to bypass the Kernel Memory Allocator.


### File Associated with a Process

Each process has its own current working directory and its own root directory. These are only two examples of data that must be maintained by the kernel to represent the interactions between a process and a filesystem. A whole data structure of type fs_struct is used for that purpose, and each process descriptor has an fs field that points to the process fs_struct{} structure.

A second table, whose address is contained in the files field of the process descriptor, specifies which files are currently opened by the process. It is a files_struct{} structure. 

For every file with an entry in the fd array, the array index is the file descriptor. 

### Filesystem Mounting

For each mount operation, the kernel must save in memory the mount point and the mount flags, as well as the relationships between the fielsystem to be mounted and the other mounted filesystems. Such information is stored in a mounted filesystem descriptor of type vfsmount{}. 


### System Calls Handled by the VFS

mount(), umount(), umount2(), mount/unmount filesystems

sysfs(), get filesystem information

statfs(), fstatfs(), stafs64(), fstatfs64(), ustat(), get filesystem statistics

chroot(), pivot_root(), change root directory

chdir(), fchdir(), getcwd() manipulate current directory

mkdir(), rmdir(), create and destroy directories

getdents(), getdents64(), readdir(), link(), ulink(), rename(), lookup_dcookie(), manipulate directory entries

readlink(), symlink(), manipulate soft links

chown(), fchown(), lchown(), chown16(), fchown16(), lchown16(), modify file owner

chmod(), fchmod(), utime(), modify file attributes

stat(), fstat(), lstat(), access(), oldstat(), oldfstat(), oldlstat(), stat64(), lstat64(), fstat64(), read file systus

open(), close(), creat(), umask(), open, close and create files

dup(), dup2(), fcntl(), fcntl64(), manipulate file descriptors

select(), poll(), wait for events on a set of file descriptors

truncate(), ftruncate(), truncate64(), ftruncate64(), change file size

lseek(), _llseek(), change file pointer

read(), write(), readv(), writev(), sendfile(), sendfile64(), readahead(), carry out file I/O operations

io_setup(), io_submit(), io_getevents(), io_cancel(), io_dentroy(), asynchronous I/O(allows multiple outstanding read and write requests)

pread64(), pwrite64(), seek file and  access it

mmap(), mmap2(), munmap(), madvise(), mincore(), remap_file_pages(), handle file memory mapping

fdatasync(), fsync(), sync(), msync(), synchronize file data

flock(), manipulate file lock

setxattr(), lsetxattr(), fsetxattr(), getxattr(), lgetxattr(), fgetxattr(), listxattr(), llistxattr(), flistxattr(), removexattr(), lremovexattr(), fremovexattr(), manipulate file extended attributes


## VFS Data Structures


### Superblock Objects

A superblock object consists of a super_block{} structure.


