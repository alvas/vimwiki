# Pages
 
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

external fragmentation: frequent requests and releases of groups of contiguous page frames of different sizes may lead to situation in which several small blocks of free page frames are "scattered" inside blocks of allocated page frames. As a result, it may become impossible to allocate a large block of contiguous page frames, even if there are enough free pages to satisfy the request.


# Memory Area Management

memory areas, with sequences of  memory cells having contiguous physical addresses and an arbitrary length.

internal fragmentation: it is caused by a mismatch between the size of the memory request and the size of the memory area alllocated to satisfy the request.


void *kmalloc(size_t size, gfp_t flags)

void kfree(const void *objp)

void *vmalloc(unsigned long size)

void vfree(const void *addr)

** The Slab Allocator

The slab allocator groups objects into caches. Each cache is a "store" of objects of the same type. The area of main memory that contains a cache is divided into slabs; each slab consists of one or more contiguous page frames that contain both allocated and free objects.

kmem_cache{}, cache descriptor

slab{}, slab descriptor

struct kmem_cache * kmem_cache_create(const char *name, unsigned int size, unsigned int align, slab_flags_t flags, void (*ctor)(void *)), to create specific caches

void kmem_cache_destroy(struct kmem_cache *s)

void *kmem_cache_alloc(struct kmem_cache *cachep, gfp_t flags)

void kmem_cache_free(struct kmem_cache *cachep, void *objp)

struct page *kmem_getpages(struct kmem_cache *cachep, gfp_t flags, int nodeid)

void kmem_freepages(struct kmem_cache *cachep, struct page *page)


* Vritual Memory Areas
* 
vm_area_struct{}: describe a single memory area over a contiguous internal in a given address space

* Page Tables
 
pgd_t{}

pmd_t{}

pte_t{}


physical page: 4KB

disk block: 512 bytes

page cache: address_space{}

buffer: in-memory representation of a single physical disk block


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


