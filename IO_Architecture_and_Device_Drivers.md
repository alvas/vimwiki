## I/O Archtecture

Any I/O device is hosted by one, and only one, buts. The bus type affects the internal design of the I/O device, as well as how the device has to be handled by the kernel.

The data path that connects a CPU to an I/O device is generically called an I/O bus. The 80x86 microprocessors use 16 of their address pins to address I/O devices and 8, 16 or 32 of their data pins to transfer data. The I/O bus, in turn, is connected to each I/O device by means of a hierarchy of hardware components including up to three elements: I/O ports, interfaces, and device controllers.


** I/O Ports

Each device connected to the I/O bus has its own set of I/O addresses, which are usually called I/O ports. 

Four special assembly language instructions called in, ins, out and outs allow the CPU to read from and write into an I/O port. While executing one of these instructions, the CPU selects the required I/O port and transfers the data between a CPU register and the port.

I/O ports may be also be mapped into addresses of the physical address space. The processor is then able to communicate with an I/O device by issuing assembly language instructions that operate directly on memory. Modern hardware devices are more suited to mapped I/O, because it is faster and can be combined with DMA.

The I/O ports of each device are structured into a set of specialized registers. The CPU writes the commands to be sent to the device into the device control register and reads a value that represents the internal state of the device from the device status register. The CPU also fetches data from the device by reading bytes from the device input register and pushes data to the device by writing bytes into the device output register.

To prevent I/O port conflict, the kernel keeps track of I/O ports assigned to each hardware device by means of "**resources**". A resource represents a portion of some entity that can be exclusively assigned to a device driver. In our case, a resource represents a range of I/O port addresses. The information relative to each resource is stored in a resource{} data structure. All resources of the same kind are inserted in a tree-like data structure; all resources representing I/O port address ranges are included in a tree rooted at the node ioport_resource.

As a general rule, each node of the tree must correspond to a subrange of the range associated with the parent. The root of the I/O port resource tree(ioport_resource) spans the whole I/O address space(form port number 0 to 65535).


