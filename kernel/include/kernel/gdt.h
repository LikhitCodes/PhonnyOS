#ifndef GDT_H
#define GDT_H

#include<stdint.h>

#define GDT_KERNEL_CODE_SELECTOR 0x08
#define GDT_KERNEL_DATA_SELECTOR 0x10
#define GDT_USER_CODE_SELECTOR 0x18
#define GDT_USER_DATA_SELECTOR 0x20
#define GDT_TSS_SELECTOR 0x28
struct gdt_entry{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
}__attribute__((packed));

struct gdt_ptr{
    uint16_t limit;
    uint32_t base;
}__attribute((packed));

void gdt_init();

#endif