#include<stdint.h>
#include<stdio.h>

__attribute__((noreturn))
void exception_handler(uint32_t vector, uint32_t error_code);

static const char *exception_names[32] = {   //32 predefined errors for cpu
    "Divide Error",
    "Debug",
    "Non-Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "x87 Floating-Point Exception",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Hypervisor Injection Exception",
    "VMM Communication Exception",
    "Security Exception",
    "Reserved"
};

void exception_handler(uint32_t vector, uint32_t error_code)
{
      if(error_code != 0){
         printf("\nCpu Exception");
         printf("\nError Vector : %d - %s Error Code : %d",vector,exception_names[vector],error_code);
      }else{
         printf("\nCpu Exception");
         printf("\nError Vector : %d - %s ",vector,exception_names[vector]);
      }
   __asm__ volatile ("cli; hlt");
}

