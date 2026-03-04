# 📌 PhonnyOS – Development Roadmap

> A custom x86-64 or 32bit (we'll see) operating system built from scratch to deeply understand kernel design, memory management, scheduling, and networking.

---

## 🔹 Phase 0 – Environment Setup

- [X] Setup x86_64-elf cross compiler
- [X] Create Makefile build system
- [X] Configure QEMU for testing
- [X] Setup GDB debugging
- [X] Setup GRUB bootloader
- [X] ISO build pipeline

---

## 🔹 Phase 1 – Boot & Kernel Initialization

- [x] Multiboot2 compliant kernel
- [X] Enter 32-bit Protected Mode
- [X] Basic kernel entry point
- [X] VGA text output driver
- [X] Clear screen + print functions
- [ ] Kernel panic handler

---

## 🔹 Phase 2 – CPU & Interrupts

- [ ] Global Descriptor Table (GDT)
- [ ] Interrupt Descriptor Table (IDT)
- [ ] CPU exception handlers
- [ ] Programmable Interrupt Timer (PIT)
- [ ] Keyboard interrupt handler
- [ ] IRQ management

---

## 🔹 Phase 3 – Memory Management

- [ ] Detect physical memory
- [ ] Bitmap-based frame allocator
- [ ] Enable paging (4-level)
- [ ] Virtual memory manager
- [ ] Kernel heap (kmalloc)
- [ ] Page fault handler

---

## 🔹 Phase 4 – Multitasking & Scheduling

- [ ] Task control block (TCB)
- [ ] Context switching
- [ ] Round-robin scheduler
- [ ] Kernel threads
- [ ] User-mode transition (Ring 3)
- [ ] Preemptive scheduling

---

## 🔹 Phase 5 – System Calls & User Programs

- [ ] Syscall interface
- [ ] Basic syscalls (write, exit)
- [ ] ELF loader
- [ ] Launch first user-space program

---

## 🔹 Phase 6 – Storage & File System

- [ ] ATA disk driver
- [ ] Virtual File System (VFS)
- [ ] FAT32 or custom file system
- [ ] Create / read / write files
- [ ] Directory support
- [ ] Basic shell with file commands

---

## 🔹 Phase 7 – Networking (Realistic Scope)

### 🖧 Hardware Layer
- [ ] PCI device scanning
- [ ] Intel e1000 network driver (QEMU compatible)

### 🌐 Network Stack
- [ ] Ethernet layer
- [ ] ARP protocol
- [ ] IPv4
- [ ] ICMP (ping)
- [ ] UDP
- [ ] Basic TCP implementation

---

## 🔹 Phase 8 – Usability Improvements

- [ ] Improved shell
- [ ] Process listing command
- [ ] Memory usage command
- [ ] Logging system
- [ ] Better terminal UI

---

## Stretch Goals

- [ ] SMP (multi-core support)
- [ ] Framebuffer graphics mode
- [ ] Basic GUI
- [ ] USB support
- [ ] POSIX-like API layer

---

## 📊 Project Status

| Component            | Status        |
|----------------------|--------------|
| Bootloader           |  Not Started |
| Kernel Core          |  Not Started |
| Memory Management    |  Not Started |
| Scheduler            |  Not Started |
| File System          |  Not Started |
| Networking           |  Not Started |

---


## Not In Scope 

- Native WiFi driver (extremely hardware-specific & firmware-dependent)
- Proprietary GPU drivers
- Production hardware compatibility

---

> Goal: Build a clean, technically sound teaching kernel that demonstrates real systems engineering fundamentals.
