# Pages

Understanding the Linux Kernel
 
* Page Tables
 
The physical address of the Page Directory in use is stored in a control register named cr3.

Each process has its own Page Global Directory and its own set of Page Tables.When a process switch occurs, Linux saves the cr3 control register in the descriptor of the process previously in execution and then loads cr3 with the value stored in the descriptor of the process to be executed next. Thus, when the new process resumes its execution on the CPU, the paging unit refers to the correct set of Page Tables.

pgd_t{}

pmd_t{}

pte_t{}


physical page: 4KB

virtual_to_page() yields the address of the page descriptor associated with the linear daddress addr.

pfn_to_page(pfn) yields the address of the page descriptor associated with the page frame having number pfn.


# Page Frame Management
 
page{}, page descriptor, is associated with physical page

* Nodes

node{}

* Zones
 
zone{}


alloc_pages(gfp_mask, order), used to request 2 order contiguous page frames. It returns the address of the descriptor of the first allocated page frame or returns NULL if the allocation failed.

alloc_page(gfp_mask), used to get a single page frame; it expands to alloc_page(gfp_mask, 0), it returns the address of the descriptor of the allocated page frame or returns NULL.

__get_free_pages(gfp_mask, order), it returns the linear address of the first allocated page.

__get_free_page(gfp_mask), expands to __get_free_pags(gfp_mask, 0)

get_zerod_page(gfp_mask), used to obtain a page frame filled with zeros; it invokes alloc_pages(gfp_mask | __GFP_ZERO, 0), return sthe linear address of the obtained page frame.

__get_dma_pages(gfp_mask, order), used to get page farmes suitable for DMA; it expands to __get_free_pages(gfp_mask | __GFP_DMA, order)



__free_pages(page, order), 

free_pages(addr, order), it receives as an argument the linear address addr of the first page frame to be released.

__free_page(page), release the page frame having the descriptor pointed to by page; it expands to __free_pages(page, 0)

free_page(addr), releases the page frame having the linear address addr; it expands to free_pages(addr, 0)


void *page_address(const struct page *page), returns the linear address associated with the page frame, or NULL if the page frame is in high memory and is not mapped.


* permanent mappings

void *kmap(struct page *page), establishes a permanent kernel mapping. Can't be invoked by interrupt handlers and deferrable functions.

void kunmap(struct page *page), destroys a permanent kernel mapping established previously by kmap().


* temporary mappings

Each fix-mapped linear address is represented by a small integer index defined in the enum fixed_address data structure:

```
enum fixed_address {
    FIX_HOLE,
    FIX_VSYSCALL,
    FIX_APIX_BASE,
    FIX_IO_APIC_BASE_0,
    ...
    __end_of_fixed_addresses
}

```
fix_to_virtual(), computes the constant linear address starting from the index

```
inline unsigned long fix_to_virt(const unsigned int idx)
{
    if (idx >= __end_of_fixed_addresses)
        __this_fixmap_does_not_exist();
        
    return (0xfffff000UL - (idx << PAGE_SHIFT));
}
```

set_fixmap(idx, phys), to associated a physical address with a fix-mapped linear address

clear_fixmap(idx), removes the linking between a fix-mapped linear address idx and the physical address

void *kmap_atomic(struct page *page), to establish a temporary kernel mapping

void kunmap_atomic(void *addr), to destroy a temporary kernel mapping



** The Buddy System Algorithm

**external fragmentation**: frequent requests and releases of groups of contiguous page frames of different sizes may lead to situation in which several small blocks of free page frames are "scattered" inside blocks of allocated page frames. As a result, it may become impossible to allocate a large block of contiguous page frames, even if there are enough free pages to satisfy the request.


# Memory Area Management

memory areas, with sequences of  memory cells having contiguous physical addresses and an arbitrary length.

**internal fragmentation**: it is caused by a mismatch between the size of the memory request and the size of the memory area allocated to satisfy the request.


** The Slab Allocator

The slab allocator groups objects into caches. Each cache is a "store" of objects of the same type. The area of main memory that contains a cache is divided into slabs; each slab consists of one or more contiguous page frames that contain both allocated and free objects.

kmem_cache{}, cache descriptor

slab{}, slab descriptor

kmem_cache_init() is invoked during system initialization to set up the general caches.

struct kmem_cache * kmem_cache_create(const char *name, unsigned int size, unsigned int align, slab_flags_t flags, void (*ctor)(void *)), to create specific caches

void kmem_cache_destroy(struct kmem_cache *s), to destroy a cache and remove it form the cache_chain list.

kmem_cache_shrink(), destroys all the slabs in a cache by invoking slab_destroy() iteratively.

The names of all general and specific caches can be obtained at runtime by reading /proc/slabinfo. This file also specifies the number of free objects and number of allocated objects in each cache.

struct page *kmem_getpages(struct kmem_cache *cachep, gfp_t flags, int nodeid)

void kmem_freepages(struct kmem_cache *cachep, struct page *page)

When slab allocator creates a new slab, it relies on the zoned page frame allocator to obtain a group of free contiguous page frames. It invokes kmem_getpages().

Page frames assigned to a slab can be released by invoking the kmem_freepages().

The slab allocator assigns a new slab to the cache by invoking cache_grow(). This function calls kmem_getpages() to obtain from the zoned page frame allocator the group of page frames needed to store a single slab; it then calls alloc_slabmgmt() to get a new slab descriptor.

The slab_destroy() function is invoked to destroy a slab and release the corresponding page frames to the zoned page frame allocator.


** Object Descriptor

Each object has a short descriptor of type kmem_bufctl_t. Object descriptors are stored in an array placed right after the corresponding slab descriptor.

An object descriptor is simply an unsigned short integer, which is meaningful only when the object is free. It contains the index of the next free object in the slab.


** Allocating a Slab Object

New objects may be obtained by invoking void *kmem_cache_alloc(struct kmem_cache *cachep, gfp_t flags)

void kmem_cache_free(struct kmem_cache *cachep, void *objp), releases an object previously allocated by the slab allocator to some kernel function.

** General Purpose Objects

memory areas are handled through a group of general caches whose objects have geometrically distributed sizes ranging from a minimum of 32 to a maximum of 131072 bytes. Objects of this type are obtained by invoking kmalloc().

void *kmalloc(size_t size, gfp_t flags)

void kfree(const void *objp), object obtained by invoking kmalloc() can be released by calling kfree().


* Noncontiguous Memory Area Management
 

** Descriptors of Noncontiguous Memory Areas

vm_struct{}, noncontiguous memory area


get_vm_area(), looks for a free range of linear addresses between VMALLOC_START and VMALLOC_END.

void *vmalloc(unsigned long size), allocates a noncontiguous memory area to the kernel.

map_vm_area(), fiddles with the page table entries used by the kernel to indicate that each page frame allocated to the noncontiguous memory area is now associated with a linear address included in the interval of contiguous linear addresses yielded by vmalloc().

void vfree(const void *addr), releases noncontiguous memory areas created by vmalloc().


vmap(), maps page frames already allocated in a noncontiguous memory area. It is similar to vmalloc(), but it does not allocate page frames.

vunmap(), releases memory ares created by vmap().


# Process Address Space

The kernel represents intervals of linear addresses by means of resources called **memory regions**, which are characterized by an initial linear address, a length, and some access rights.


** System calls related to memory region creation and deletion

brk(), changes the heap size of the process

execve(), loads a new executable file, thus changing the process address space

_exit(), terminates the current process and destroys its address space

fork(), creates a new process, and thus a new address space

mmap(), mmap2(), creates a memory mapping for a file, thus enlarging the process address space

mremap(), expands or shrinks a memory region

remap_file_pages(), creates a non-linear mapping for a file

munmap(), destroy a memory mapping for a file, thus contracting the process address space

shmat(), attaches a shared memory region

shmdt(), detaches a shared memory region


** The Memory Descriptor

All information related to the process address space is included in an object called the memory descriptor of type mm_struct. This object is referenced by the mm field of the process descriptor.

mm_struct{}, memory descriptor

** Memory Descriptor of Kernel Threads

Kernel threads run only in Kernel Mode, so they never access linear addresses below TASK_SIZE(same as PAGE_OFFSET, usually 0xc0000000). Kernel threads do not use memory regions, therefore most of the fields of a memory descriptor are meaningless for them.

** Memory Regions (Virtual Memory Areas)

vm_area_sturct{}, memory region descriptor, describe a single memory area over a contiguous internal in a given address space


Kernel threads never use linear addresses below TASK_SIZE. Similarly, interrupt handlers, deferrable functions, and code of critical regions should not use linear addresses below TASK_SIZE because this might block the current process.


# The Page Cache

disk cache is a software mechanism that allows the system to keep in RAM some data that is normaly stored on a disk, so that further accesses to that data can be satisfied quickly without accessing the disk.

The dentry cache, which stores dentry bojects representing filesystem pathnames, and the inode cache, which stores inode objects representing disk inodes.

The page cache, which is a disk cache working on whole pages of data.

** The Page Cache

The page cache is the main disk cached. In most cases, the kernel refers to the page cache when reading from or writing to disk. New pages are added to the page cache to satisfy User Mode proceeses's read requests.

Each page included in the page cache contains data belonging to some file. The file -- or more precisely the file's inode -- is called the page's owner.Pratically all read() and write() file operations rely on the page cache. A page in the page cache is identified by an owner and by an index within the owner's data, an inode and an offset inside the corresponding file.

** The address_space Object

The core data structure of the page cache is the address_space object, a data structure embedded in the inode object that owns the page. Many pages in the cache may refer to the same owner, thus they may be linked to the same address_space object.

page cache: address_space{}

The owner of a page is the page cache is a file, the address_space object is embedded in the i_data field of the VFS inode object. The i_mapping field of the inode always points to the address_space object of the owner of the pages containing the inode's data. The host field of the address_space object points to the inode object in which the descriptor is embedded.


** The Radix Tree

The page_tree field of an address_space object is the root of a radix tree, which contains pointers to the descriptors of the owner's pages. Each node is represented by the radix_tree_node{} data structure.


** Storing Blocks in the Page Cache

*** Block Buffers and Buffer Heads

Each block buffer has a buffer head descriptor of type buffer_head{}. This descriptor contains all the information needed by the kernel to know how to handle the block; thus, before operating on each block, the kernel checks its buffer head. If the page is in high memory, the b_data field contains the offset of the block buffer with respect to the beginning of the page; otherwise, b_data contains the linear address of the block buffer.

*** Buffer Pages

Here are two common cases in which the kernel creates buffer pages:

* When reading or writing pages of a file that are not stored in contiguous disk blocks.
* When accessing a single disk block. This kind of buffer pages must satisfy a strong constraint: all the block buffer must refer to adjacent blocks of the underlying block device.

buffer: in-memory representation of a single physical disk block

disk block: 512 bytes


# Page Frame Reclaiming

** Reverse Mapping


*** Reverse Mapping for Anonymous Pages

When the kernel assigns the first page frame to an anonymous region, it creates a new anon_vma{} daa structure. The kernel stores the address of the anon_vma{} data structure in the mapping field of the descriptor of the anonymous page.


** Swapping

Swapping has been introduced to offer a backup on disk for unmapped pages. 

*** Swap Area

The pages swapped out from memory are stored in a swap area, which may be implemented either as a disk partition of its own or as a file included in a large partition.

Each swap area consists of a sequence of page slots: 4096-byte blocks used to contain a swapped-out page. The first page slot of a swap area is used to persistently store some information about the swap area; its format is described by the swap_header union composed of two structures, info and magic.


*** Swap Area Descriptor

Each active swap area has its own swap_info_struct{} descriptor in memory. 

*** Swapped-Out Page Identifier

A swapped-out page is uniquely identified quite simply by specifying the index of the swap area in the swap_info_array and the page slot index inside the swap area.


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


