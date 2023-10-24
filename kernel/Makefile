CXX = aarch64-linux-gnu-gcc
CXXFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles

LD = aarch64-linux-gnu-ld
LDFLAGS = -T linker.ld

OD = aarch64-linux-gnu-objdump

OBJCOPY = aarch64-linux-gnu-objcopy
OBJCOPYFLAGS = -O binary

GDB = aarch-gdb
GDBFLAGS = -x ./debug.gdb

BUILD_DIR = build
SRC = $(wildcard test/*.S) $(wildcard test/*.c) $(wildcard lib/*.c)
OBJ = boot.o $(filter-out boot.o, $(wildcard *.o))
INC = $(wildcard ../lib/)

BOOT = kernel8
ELF = $(BOOT).elf
IMG = $(BOOT).img

all:
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC) -c -g $(SRC)
	make kernel8

kernel8:
	$(LD) $(LDFLAGS) $(BUILD_DIR)/$(ELF) $(OBJ)
	$(OBJCOPY) $(OBJCOPYFLAGS) $(BUILD_DIR)/$(ELF) $(BUILD_DIR)/$(IMG)
	$(OD) -D $(BUILD_DIR)/$(ELF) > $(BUILD_DIR)/$(BOOT).objdump
	$(OD) -x $(BUILD_DIR)/$(ELF) > $(BUILD_DIR)/$(BOOT).xobjdump
	$(OD) -s $(BUILD_DIR)/$(ELF) > $(BUILD_DIR)/$(BOOT).content
	rm $(OBJ)

debug:
	qemu-system-aarch64 -M raspi3b\
		-kernel $(BUILD_DIR)/$(IMG)\
		-display none\
		-serial null\
		-serial stdio\
		-S -s

run:
	qemu-system-aarch64 -M raspi3b\
		-kernel $(BUILD_DIR)/$(IMG)\
		-display none\
		-serial null\
		-serial stdio\
		-initrd ../initramfs.cpio

test:
	qemu-system-aarch64 -M raspi3b\
		-kernel $(BUILD_DIR)/$(IMG)\
		-display none\
		-serial null\
		-serial stdio\
		-serial pty\
		-initrd ../initramfs.cpio

gdb:
	$(GDB) $(GDBFLAGS)

clean:
	rm -rf $(BUILD_DIR)
	rm *.o
