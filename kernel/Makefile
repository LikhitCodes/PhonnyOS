DEFAULT_HOST!=../default-host.sh
HOST?=$(DEFAULT_HOST)
HOSTARCH!=../target-triplet-to-arch.sh $(HOST)

CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include

BUILDDIR=build

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_kernel -Iinclude
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -nostdlib -lk -lgcc

ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config

CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)

KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) \
kernel/kernel.o \

OBJS=\
$(BUILDDIR)/$(ARCHDIR)/runtime/crti.o \
$(BUILDDIR)/$(ARCHDIR)/crtbegin.o \
$(addprefix $(BUILDDIR)/,$(KERNEL_OBJS)) \
$(BUILDDIR)/$(ARCHDIR)/crtend.o \
$(BUILDDIR)/$(ARCHDIR)/runtime/crtn.o \

LINK_LIST=\
$(BUILDDIR)/$(ARCHDIR)/runtime/crti.o \
$(BUILDDIR)/$(ARCHDIR)/crtbegin.o \
$(addprefix $(BUILDDIR)/,$(KERNEL_OBJS)) \
$(LIBS) \
$(BUILDDIR)/$(ARCHDIR)/crtend.o \
$(BUILDDIR)/$(ARCHDIR)/runtime/crtn.o \

.PHONY: all clean install install-headers install-kernel

all: phonnyos.kernel

phonnyos.kernel: $(OBJS) $(ARCHDIR)/linker/linker.ld
	$(CC) -T $(ARCHDIR)/linker/linker.ld -o $@ $(CFLAGS) $(LINK_LIST)
	grub-file --is-x86-multiboot phonnyos.kernel

$(BUILDDIR)/$(ARCHDIR)/crtbegin.o $(BUILDDIR)/$(ARCHDIR)/crtend.o:
	mkdir -p $(dir $@)
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

$(BUILDDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

$(BUILDDIR)/%.o: %.S
	mkdir -p $(dir $@)
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

clean:
	rm -rf build
	rm -f phonnyos.kernel

install: install-headers install-kernel

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-kernel: phonnyos.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp phonnyos.kernel $(DESTDIR)$(BOOTDIR)

-include $(OBJS:.o=.d)