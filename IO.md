## I/O Archtecture

Any I/O device is hosted by one, and only one, buts. The bus type affects the internal design of the I/O device, as well as how the device has to be handled by the kernel.

The data path that connects a CPU to an I/O device is generically called an I/O bus. The 80x86 microprocessors use 16 of their address pins to address I/O devices and 8, 16 or 32 of their data pins to transfer data. The I/O bus, in turn, is connected to each I/O device by means of a hierarchy of hardware components including up to three elements: I/O ports, interfaces, and device controllers.


### I/O Ports

Each device connected to the I/O bus has its own set of I/O addresses, which are usually called I/O ports. 

Four special assembly language instructions called in, ins, out and outs allow the CPU to read from and write into an I/O port. While executing one of these instructions, the CPU selects the required I/O port and transfers the data between a CPU register and the port.

I/O ports may be also be mapped into addresses of the physical address space. The processor is then able to communicate with an I/O device by issuing assembly language instructions that operate directly on memory. Modern hardware devices are more suited to mapped I/O, because it is faster and can be combined with DMA.

The I/O ports of each device are structured into a set of specialized registers. The CPU writes the commands to be sent to the device into the device control register and reads a value that represents the internal state of the device from the device status register. The CPU also fetches data from the device by reading bytes from the device input register and pushes data to the device by writing bytes into the device output register.

To prevent I/O port conflict, the kernel keeps track of I/O ports assigned to each hardware device by means of "**resources**". A resource represents a portion of some entity that can be exclusively assigned to a device driver. In our case, a resource represents a range of I/O port addresses. The information relative to each resource is stored in a resource{} data structure. All resources of the same kind are inserted in a tree-like data structure; all resources representing I/O port address ranges are included in a tree rooted at the node ioport_resource.

As a general rule, each node of the tree must correspond to a subrange of the range associated with the parent. The root of the I/O port resource tree(ioport_resource) spans the whole I/O address space(form port number 0 to 65535).

The tree of all I/O addresses currently assigned to I/O devices can be obtained from the /proc/ioports file.


### I/O Interfaces

An I/O interface is a hardware circuit inserted between a group of I/O ports and the corresponding device controller. It acts as an interpreter that translates the values in the I/O ports into commands and data for the device. In the opposite direction, it detects changes in the device state and correspondingly updates the I/O port that plays the role of status register. This circuit can also be connected through an IRQ line into a Programmable Interrupt Controller, so that it issues interrupt requests on behalf of the device.



**Motor drivers vs Motor controllers(Practical Robotics in C++)**

+ Motor drivers are the **circuitry** that handles supplying power to the motors based on their input signal.
+ Motor controllers are the **software and circuitry** that take an input signal about what the motor needs to be doing, and generates and output signal that goes to the motor drivers.


### The Device Driver Model


#### The sysfs Filesystem

The /proc filesystem was the first special filesystem designed to allow User Mode applications to access kernel internal data structures. The /sysfs filesystem has essentially the same objective, but it provides additional information on kernel data structures; furthermore, /sysfs is organized in a more structure way than /proc.

A goal of the sysfs filesystem is to expose the hierarchical relationships among the components of the device driver model.

Top-level directories of this filesystem:
+ block
+ devices
+ bus
+ drivers
+ class
+ power
+ firmware

Relationships between components of the device driver models are expressed in the sysfs filesystem as symbolic links between directories and files. The main role of regular files in the sysfs filesystem is to represent attributes of drivers and devices.


#### Kobjects

The core data structure of the device driver model is a generic data structure named kobject{}, which is inherently tied to the sysfs filesystem: each kobject corresponds to a directory in that filesystem.

A kset{} is a collection of kobjects of the same type. 

Collections of ksets called subsystems. A subsystem may include ksets of different types, and it is represented by a subsystem{} data structure.

The kobject_register() function initializes a kobject and adds the corresponding directory to the sysfs filesystem.

The kobject_unregister() function removes a kobject's directory from the sysfs filesystem.

Many kobject directories include regular files called attributes. The sysfs_create_file() function receive as its parameters the addresses of a kobject and an attribute descriptor, and creates the special file in the proper directory. Other relationships between the objects represented in the sysfs filesystem are established by means of symbolic links: the sysfs_create_link() function creates a symbolic link for a given kobject in a directory associated with another kobject.


## Components of the Device Driver Model


### Devices

Each device in the device driver model is represented by a device{} object.

The device objects are globally collected in the devices_subsys subsystem, which is associated with the /sys/devices directory. 

The device_register() function inserts a new device object in the device driver model, and automatically creates a new directory for it under /sys/devices. Conversely, the device_unregister() function removes a device from the device driver model. Usually, the device object is statically embedded in a larger descriptor.


### Drivers

Each driver in the device driver model is described by a device_driver{} object. The driver_register() function inserts a new device_driver object  in the device driver model, and automatically creates a new directory for it in the sysfs filesystem. Conversely, the driver_unregister() function removes a driver from the device driver model. Usually, the device_driver object is statically embedded in a larger descriptor.


### Buses

Each bus type supported by the kernel is described by a bus_type{} object. Each bus_type object includes an embedded subsystem; the subsystem stored in the bus_subsys variable collects all subsystems embedded in the bus_type objects. The bus_subsys subsystem is associated with the /sys/bus directory. Because the directories of the devices' kobjects already appear in the sysfs filesystem under /sys/devices, the devices directory of the per-bus sybsystem stores symbolic links pointing to directories under /sys/devices.


### Classes

Each class is described by a class{} object. All class objects belong to the class_subsys subsystem associated with /sys/class directory. Each class object includes an embedded subsystem.


## Device Files

I/O devices are treated as special files called device files. 

Network cards are a notable exception to this schema, because they are hardware devices that are not directly associated with device files. 

A device file is usually a real file stored in a filesystem. Its inode doesn't need to include pointers to blocks of data on the disk(the file's data) because there are none. Instead the inode must include an identifier of the hardware device corresponding to the character or block device file. Traditionally, this identifier consists of the type of device file(character or block) and a pair of numbers. The first number, called the major number, identifies the device type. Traditionally, all device files that have the same major number and the same type share the same set of file operations, because they are handled by the same device driver. The second number, called the minor number, identifies a specific device among a group of devices that share the same major number.

The mknod() system call is used to create device files. It receives the name of the device file, its type, and the major and minor numbers as its parameters. Device files are usually included in the /dev directory. 

The major and minor numbers are stored in the dev attributes contained in the subdirectories of /sys/class.

The VFS changes the default file operations of a device file when it is opened; as a result, each system call on the device file is translated to an invocation of a device-related function instead of the corresponding function of the hosting filesystem.


## Device Drivers

A device driver is the set of kernel routines that makes a hardware device respond to the programming interface defined by the canonical set of VFS functions(open, read, lseek, ioctl and so forth) that control a device. The actual implementation of all these functions is delegated to the device driver. 

Each system call issued on a device file is translated by the kernel into an invocation of a suitable function of a corresponding device driver. 


### Device Driver Registration

To properly handle a generic PCI device, its device driver must allocate a descriptor of type pci_driver, which is used by the PCI kernel layer to handle the device. After having initialized some fields of this descriptor, the device driver invokes the pci_register_driver() function. Actually the pci_driver descriptor includes an embedded device_driver descriptor; the pci_register_function() simply initializes the fields of the embedded driver descriptor and invokes driver_register() to insert the driver in the data structures of the device driver model.

When a device driver is being registered, the kernel looks for unsupported hardware devices that could be possibly handled by the driver. To do this, it relies on the match method of the relevant bus_type bus type descriptor in device_driver object, and on the probe method of the device_driver object. If a hardware device that can be handled by the driver is discovered, the kernel allocates a device object and invokes device_register() to insert the device in the device driver model.

### Device Driver Initialization

Initializing a driver means allocating precious resources(IRQs page fames for DMA transfer buffers, DMA channel) of the system, which are therefore not available to other drivers.

### Direct Memory Access(DMA)


## Character Device Drivers

A character device driver is described by a cdev{} structure.

The cdev_alloc() function allocates dynamically a cdev descriptor and initializes the embedded object so that the descriptor is automatically freed when the reference counter becomes zero.

The cdev_add() function registers a cdev descriptor in the device driver model. The function initializes the dev and count fields of the cdev descriptor, and then invokes the kobj_map() function. This function sets up the device driver model's data structures that glue the interval of device numbers to the device driver descriptor.


cdev{} is driver; char_device_struct{} is device.


### Block Device Drivers

In general, each I/O operation involves a group of blocks that are adjacent on disk. Each I/O operation is represented by a "block I/O"(bio) structure, which collects all information needed by the lower components to satisfy the request.


* The controllers of the hardware block devices transfer data in chunks of fixed length called "sectors". Therefore, the *I/O scheduler* and the *block device drivers* must manage *sectors* of data.
* * The *Virtual Filesystem, the mapping layer, and the filesystems* group the disk data in logical units called "*blocks*". A block corresponds to the minimal disk storage unit inside a filesystem.
* *Block device drivers* should be able to cope with "*segments*" of data: each segment is a memory page - or a portion of a memory page - including chunks of data that are physically adjacent on disk.
* The *disk caches* work on "*pages*" of disk data, each of which fits in a page frame.
* The *generic block layer* glues together all upper and lower components, thus it knows about *sectors, blocks, segments, and pages* of data.


#### Sectors

To achieve acceptable performance, **hard disks and similar devices** transfer several adjacent bytes at once. Each data transfer operation for a block device acts on a group of adjacent bytes called a sector. In most disk devices, the size of a sector is 512 bytes. Sector should be considered as the basic unit of data transfer. Sector indices are stored in 32- or 64-bit variables of type sector_t{}.


#### Blocks

The block is the basic unit of data transfer for the VFS and, consequently, for the filesytems. The block size is not specific to a block device. When creating a disk-based filesystem, the administrator may select the proper block size. Several partitions on the same disk might make sue of different block sizes. Each read or write operation issued on a block device file is a "raw" access that bypasses the disk-based filesyste; the kernel executes it by using blocks of largest size(4,096 bytes). Each block requires its own block buffer, which is a RAM memory area used by the kernel to store the block's content. The size of a block buffer always matches the size of the corresponding block. Each buffer has a "buffer head" descriptor of type buffer_head{}.


#### Segments

In almost all cases, the data transfer is directly performed by the disk controller with a DMA operation. The block device driver simply triggers the data transfer by sending suitable commands to the disk controller; once the data transfer is finished, the controller raises and interrupt to notify the block device driver. The data transferred by a single DMA operation must belong to sectors that are adjacent on disk. So-called scatter-gather DMA transfers: in each such operation, the data can be transfered from or to several noncontiguous memory areas. To make use of scatter-gather DMA operations, block device drivers must handle the data in units called segments. A segment is simply a memory page - or a port of a memory page - that includes the data of some adjacent disk sectors. Thus, a scatter-gather DMA operation may involve several segment at once.


### The Generic Block Layer

#### The Bio Structure

The core data structure of the generic block layer is a descriptor of an ongoing I/O block device operation called bio{}. Each bio essentially includes an identifier for a disk storage area -- the initial sector number and the number of sectors included in the storage area -- and one or more segments describing the memory areas involved in the I/O operation. 

Each segment in a bio is represetned by a bio_vec{} data structure.


The contents of a bio descriptor keep changing during the block I/O operation. When the generic block layer starts a new I/O operation, it allocates a new bio structure by invoking the bio_alloc() function.


#### Representing Disk and Disk partitions

A disk is a logical block device that is handled by the generic block layer. A disk can be a virtual device built upon several physical disk partitions, or a storage area living in some dedicated pages of RAM. 

A disk is represented by the gendisk{} object. 

The fops field of the gendisk object points to a block_device_operations table: open(), release(), ioctl(), compat_ioctl(), media_changed(), revalidate_disk()

Hard disks are commonly split into logical partitions. Each block device file may represent either a whole disk or a partition inside the disk.

If a disk is split in partitions, their layout is kept in an array of hd_struct{} structures whose address is stored in the part field of the gendisk object.

When the kernel discovers a new disk in the system, it invokes the alloc_disk() function, which allocates and initializes a new gendisk object and, if the new disk is split in several partitions, a suitable array of hd_struct descriptors. Then, it invokes the add_disk() function to insert the new gendisk descriptor into the data structures of the generic block layer.

#### Submitting a Request

bio_alloc() to allocate a new bio descriptor. The kernel invokes the generic_make_request() which is the main entry point of the generic block layer. 


#### Request Descriptors

Each pending request for a block device is represented by a request{}. Each request consists of one or more bio structures. 


### The I/O Scheduler

When a kernel component wishes to read or write some disk data, it actually creates a block device request. The generic block layer invokes the I/O scheduler to create a new block device request or to enlarge an already existing one and then terminates. Each block device driver maintains its own request queue, which contains the list of pending requests for the device. If the disk controller is handling several disks, there is sually one request queue for each physical block device. 

#### Request Queue Descriptors

Each request queue is represented by means of a large request_queue{}. 


#### Activating the Block Device Driver

The delay activation of the block device driver is accomplished through a technique know as device plugging and unplugging. As long as block device driver is plugged, the device driver is not activated even if there are requests to be processed in the driver's queues.

The blk_plug_device() function plugs a block device -- or more precisely, a request queue serviced by some block device driver.

The blk_remove_plug() function unplugs a request queue.


#### I/O Scheduling Algorithms

To change the I/O scheduler used in the master disk of the first IDE channel, the administrator can write an elevator name into the /sys/block/hda/queue/scheduler file of the sysfs special filesystem. 


### Block Device Drivers

#### Block Devices

The block device driver must take care of all VFS system calls issued on the block device files associated with the corresponding block devices. 

Each block device is represented by a block_device{} descriptor.

All block device descriptors are inserted in a global list, whose head is represented by the all_bdevs variable; the pointers for list linkage are in the bd_list field of the block device descriptor. 

The relationship between a major and minor number and the corresponding block device descriptor is maintained through the bdev special filesystem. 

#### Device Driver Registration and Initialization

register_blkdev(), device driver reserve a major number for its own purposes.

alloc_disk(), allocates disk descriptor, allocates the array that stores the partition descriptors of the disk.

The driver needs to register the IRQ line for the device:

```
request_irq(foo_irq, foo_interrupt, SA_INTERRUPT | SA_SHIRQ, "foo", NULL),
```

Registering and activating the disk:

```
add_disk(foo.gd);
```

add_disk(), receives as its parameter the address of the gendisk descriptor.


### Opening a Block Device File

The kernel opens a block device file every time that a filesystem is mounted over a disk or partition, every time that a swap partition is activated, and every time that a User Mode process issues an open() system call on a block device file. 

The f_op field of the file object is set to the address of the def_blk_fops table. 

The blkdev_open() method is invoked by the dentry_open().
