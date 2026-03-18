#ifndef IDT_H
#define IDT_H

#include<stdint.h>

typedef struct idt_entry
{
    uint16_t isr_low;
    uint16_t kernel_cs;
    uint8_t reserved;
    uint8_t attributes;
    uint16_t isr_high; 
}__attribute__((packed)) idt_entry_t;

typedef struct idtr
{
    uint16_t limit;
    uint32_t base;
}__attribute__((packed)) idtr_t;

void idt_set_descriptor(uint8_t entries, void * isr, uint8_t flags);
void idt_init();

#endif