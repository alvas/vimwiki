0xfffffff0 BIOS -> first sector(boot loader 1) 0x00007c00 -> (boot loader 2) 0x00096c00 -> first 512 bytes of the kernel 0x00090000 -> setup() 0x00090200 -> reset of kernel image 0x00100000 -> startup_32() decompress kernel -> startup_32() setup process 0 execution environment -> start_kernel()

# BIOS
to begin the boot, a speical hardware circuit raises the logical value of the RESET pin of the CPU. After RESET is asserted, some registers of the process(including cs and eip) are set to fixed values, and the code found at physical address 0xfffffff0 is executed.

A real mode address is composed of a seg segment and an off offset; the corresponding physical address is given by seg*16+off.

1. execute Power-On Self-Test(POST). The boostrap code in an ACPI-compliant BIOS builds several tables that describe the hardware devices present in the system.
2. initializes the hardware devices.
3. search for an operating system to boot. the first sector(boot sector)
4. As soon as a valid device is found, it copies the contents of its first sector into RAM, starting from physical address 0x00007c00, and then jumps into that address and executes the code just loaded.

# Boot Loader
The boot lader is the program invoked by the BIOS to load the image of an operating system kernel into RAM.

The first sector of the hard disk, name the Master Boot Record(MBR), includes the partition table and a small program, which loads the first sector of the partition containing the operating system to be started.

The LILO boot loader is too large to fit into a single sector, thus it is broken into two parts. The MBR or the partition boot sector includes a small boot loader, which is loaded into RAM starting from address 0x00007c00 by the BIOS. This small program moves itself to the address 0x00096a00, sets up the Real Mode stack(ranging from 0x00098000 to 0x000969ff), loads the second part of the LILO boot loader into RAM starting from address 0x00096c00, and jumps into it.

After the user has chosen the kernel to be loaded, the boot loader may either copy the boot sector of the corresponding partition into RAM and execute it or directly copy the kernel image into RAM.

The LILO boot loader invokes a BIOS procedure to load an initial portion of the kernel image from disk: the first 512 bytes of the kernel image are put in RAM at address 0x00090000, while the code of the setup() function is put in RAM starting from address 0x00090200. It invokes a BIOS procedure to load the rest of the kernel image form disk and puts the image in RAM starting from either low address 0x00010000 or high address 0x00100000.

# setup()
The code of the setup() assembly language function has been placed by the linker at offset 0x200 of the kernel image file. The boot loader can therefore easily locate the code and copy it into RAM, starting from physical address 0x00090200. The setup() function initialize the hardware devices and set up the environment for the execution of the kernel program. It sets up a provisional Interrupt Descriptor Table(IDT) and a provisional global Descriptor Table(GDT).

# startup_32()
1. arch/i386/boot/compressed/head.S, startup_32(). Decompress kernel. The decompressed image is then moved into its final position, which starts at physical address 0x00100000.
2. arch/i386/kernel/head.S, startup_32(). It sets up the execution environment for the first Linux process(process 0).

# start_kernel()
* sched_init()
* build_all_zonelists()
* page_alloc_init(), mem_init()
* trap_init, init_IRQ()
* softirq_init()
* time_init()
* kmem_cache_init()
* calibrate_delay()
* kernel_thread()


