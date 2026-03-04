#include <kernel/gdt.h>

#define GDT_ENTRIES 6

struct gdt_entry gdt[GDT_ENTRIES];
struct gdt_ptr gp;

extern void gdt_flush(uint32_t);

static void gdt_set_gate(int num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0x0F;

    gdt[num].granularity |= gran & 0xF0;
    gdt[num].access = access;
}

void gdt_init()
{
    gp.limit = sizeof(struct gdt_entry) * GDT_ENTRIES -1 ;
    gp.base = (uint32_t)&gdt;

    //Null descriptor
    gdt_set_gate(0,0,0,0,0);

    //Kernel Code Descriptor
    gdt_set_gate(1,0,0xFFFFFFFF,0x9A,0xCF);

    //Kernel Data Descriptor
    gdt_set_gate(2,0,0xFFFFFFFF,0x92,0xCF);

    //User Code Descriptor
    gdt_set_gate(3,0,0xFFFFFFFF,0xFA,0xCF);

    //User Data Decsriptor
    gdt_set_gate(4,0,0xFFFFFFFF,0xF2,0xCF);

    //TSS 
    gdt_set_gate(5,0,0,0,0);

    gdt_flush((uint32_t)&gp);
}


