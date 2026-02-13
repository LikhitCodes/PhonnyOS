/* Bootstrap assembly - the piece of code which will tell the GRUB that this is my kernel */

#  align loaded modules on page boundaries
.set ALIGN, 1<<0
#  provide memory map
.set MEMINFO, 1<<1
# this is the multiboot 'flag' field
.set FLAGS, ALIGN | MEMINFO
# magic number lets bootloader find the header
.set MAGIC, 0x1BADB002
# chemsum of above
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# defining the stack for c/cpp programs
.section .bss
.align 16
stack_bottom:
 .skip 16384 # 16 KiB
stack_top:

.section .text
.global _start
.type _start, @function
_start :
    
    # the bootloader has now loaded us into 32 bit  protected mode on a x86 machine.
     # Interrupts and paging is disabled

     mov $stack_top, %esp

     call kernel_main

     cli
     1: hlt
     jmp 1b

     .size _start, . - _start
