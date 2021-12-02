* Pages
 
page{}, is associated with physical page

* Zones
 
zone{}


struct page *alloc_pages(gfp_t gfp_mask, unsigned int order)

long __get_free_pages(gfp_t gfp_mask, unsigned int order)

void *page_address(const struct page *page)

void free_pages(unsigned long addr, unsigned int order)

void __free_pages(struct page *page, unsigned int order)

void *kmalloc(size_t size, gfp_t flags)

void kfree(const void *objp)

void *vmalloc(unsigned long size)

void vfree(const void *addr)


kmem_cache{},

struct kmem_cache * kmem_cache_create(const char *name, unsigned int size, unsigned int align, slab_flags_t flags, void (*ctor)(void *))

void kmem_cache_destroy(struct kmem_cache *s)

void *kmem_cache_alloc(struct kmem_cache *cachep, gfp_t flags)

void kmem_cache_free(struct kmem_cache *cachep, void *objp)

struct page *kmem_getpages(struct kmem_cache *cachep, gfp_t flags, int nodeid)

void kmem_freepages(struct kmem_cache *cachep, struct page *page)

* permanent mappings

void *kmap(struct page *page)

void kunmap(struct page *page)

* temporary mappings

void *kmap_atomic(struct page *page)

void __kunmap_atomic(void *addr)


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


