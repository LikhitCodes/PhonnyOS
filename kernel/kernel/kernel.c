#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/gdt.h>
#include<kernel/idt.h>

void kernel_main(void) {
	gdt_init();
	idt_init();
	terminal_initialize();
	printf("Hello, kernel World!\n");
	printf("This is our OS");
	 // test
    // __asm__ volatile (
    //     "movl $10, %%eax\n"
    //     "xorl %%edx, %%edx\n"
    //     "movl $0, %%ebx\n"
    //     "divl %%ebx"
    //     :
    //     :
    //     : "eax", "ebx", "edx"
    // );
}
