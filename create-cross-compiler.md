# Cross-Compiler Build Documentation (i686-elf)

[ BUILD LOG :: TARGET=i686-elf :: HOST=x86_64-pc-linux-gnu ]

---

## 1. Objective

Built a freestanding GCC cross-compiler toolchain targeting i686-elf for operating system development.

Purpose:
* Compile kernel code in a freestanding environment
* Avoid host (Linux/glibc) linkage
* Produce bare-metal ELF binaries

Host platform:
* OS: Arch Linux
* Architecture: x86_64

Target platform:
* Architecture: 32-bit x86
* ABI: ELF (bare metal)
* Triplet: i686-elf

---

## 2. Directory Layout

Created isolated workspace to avoid system pollution.
```
$HOME/
├── src/                # Source + build workspace
│   ├── binutils-2.42/
│   ├── gcc-14.2.0/
│   ├── build-binutils/
│   └── build-gcc/
|   └── build-gdb/
│
└── opt/
    └── cross/          # Installed cross toolchain

```
---

## 3. Environment Variables

Configured build environment:

```bash
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

Purpose:

    PREFIX -> install location

    TARGET -> output architecture

    PATH -> allows toolchain detection
```
---

## 4. Dependencies Installed (Arch)

Installed required build dependencies via pacman:
```Bash

sudo pacman -S --needed \
  base-devel \
  git \
  gmp \
  mpfr \
  libmpc \
  isl \
  texinfo \
  wget

Used for:

    GCC math libraries

    Build tooling

    Documentation tools
```
---
## 5. Source Code Download

Downloaded GNU releases into $HOME/src.
Binutils
```Bash

wget [https://ftp.gnu.org/gnu/binutils/binutils-2.42.tar.xz](https://ftp.gnu.org/gnu/binutils/binutils-2.42.tar.xz)
tar xf binutils-2.42.tar.xz

GCC
Bash

wget [https://ftp.gnu.org/gnu/gcc/gcc-14.2.0/gcc-14.2.0.tar.xz](https://ftp.gnu.org/gnu/gcc/gcc-14.2.0/gcc-14.2.0.tar.xz)
tar xf gcc-14.2.0.tar.xz
```
---
## 6. Building Binutils

Created out-of-tree build directory:
```Bash

mkdir build-binutils
cd build-binutils
```
Configured:
```Bash

../binutils-2.42/configure \
  --target="$TARGET" \
  --prefix="$PREFIX" \
  --with-sysroot \
  --disable-nls \
  --disable-werror
```
Compiled and Installed:
```Bash

make -j$(nproc)
make install

Tools produced in $HOME/opt/cross/bin/:

    i686-elf-as

    i686-elf-ld

    i686-elf-objcopy

    i686-elf-objdump
```
---

## 7. GDB Build Attempt (Optional)

Downloaded:
```Bash

wget [https://ftp.gnu.org/gnu/gdb/gdb-15.2.tar.xz](https://ftp.gnu.org/gnu/gdb/gdb-15.2.tar.xz)
tar xf gdb-15.2.tar.xz
```
Configured:
```Bash

../gdb-15.2/configure \
  --target="$TARGET" \
  --prefix="$PREFIX" \
  --disable-werror

Note: Encountered build errors due to bundled readline incompatibility with host toolchain. Resolution path: Use --with-system-readline or skip for initial development phases.
```
---
## 8. Building GCC (Freestanding)

Created build directory:
```Bash

mkdir build-gcc
cd build-gcc
```
Configured minimal freestanding compiler:
```Bash

../gcc-14.2.0/configure \
  --target="$TARGET" \
  --prefix="$PREFIX" \
  --disable-nls \
  --enable-languages=c \
  --without-headers
```
Compiled:
```Bash

make all-gcc -j$(nproc)
make all-target-libgcc -j$(nproc)
```
Installed:
```Bash

make install-gcc
make install-target-libgcc
```
---
## 9. Toolchain Verification

Confirmed binaries in $PREFIX/bin:
```
    i686-elf-gcc

    i686-elf-ld

    i686-elf-as
```
Version check:
```Bash

i686-elf-gcc --version
```
---

## 10. PATH Configuration

Permanent configuration for Bash:
```Bash

echo 'export PATH="$HOME/opt/cross/bin:$PATH"' >> ~/.bashrc
source ~/.bashrc
```
---
## 11. Freestanding Compilation Model
```
Kernel code must be compiled with: -ffreestanding

Reasoning:

    No standard C library (libc)

    No OS runtime environment

    No hosted environment assumptions

Standard headers available in freestanding mode:

    <stdint.h>

    <stddef.h>

    <stdbool.h>

    <stdarg.h>
```
