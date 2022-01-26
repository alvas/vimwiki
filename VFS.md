# The Virtual Filesystem

Five standard Unix file types: regular files, directories, symbolic links, device files and pipes

The Virtual Filesystem is a kernel software layer that handles all system calls related to a standard Unix filesystem. 

Filesystems  supported by the VFS may be grouped into three main classes:
* Disk-based filesystems
* Network filesystems
* Special filesystems

The root directory is contained in the root filesystem, which in Linux, is usually of type Ext2 or Ext3. All other filesystems can be "mounted" on subdirectories of the root filesystem. A useful feature of Linux's VFS allows it to handle virtual block devices such as /dev/loop0, which may be used to mount filesystems stored in regular files. 
