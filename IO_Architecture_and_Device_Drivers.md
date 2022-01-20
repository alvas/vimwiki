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

### Buses


### Drivers


### Classes


## Device Files



## Character Device Drivers

A character device driver is described by a cdev{} structure.

The cdev_alloc() function allocates dynamically a cdev descriptor and initializes the embedded object so that the descriptor is automatically freed when the reference counter becomes zero.

The cdev_add() function registers a cdev descriptor in the device driver model. The function initializes the dev and count fields of the cdev descriptor, and then invokes the kobj_map() function. This function sets up the device driver model's data structures that glue the interval of device numbers to the device driver descriptor.


cdev{} vs char_device_struct{}


