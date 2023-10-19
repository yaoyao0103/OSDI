CXX = aarch64-linux-gnu-gcc
CXXFLAGS = -Ilib -Itest -Wall -ffreestanding -nostdinc -nostdlib -nostartfiles

LINKER = aarch64-linux-gnu-ld

OD = aarch64-linux-gnu-objdump

OBJCOPY = aarch64-linux-gnu-objcopy
OBJCOPYFLAGS = -O binary

GDB = aarch-gdb
GDBFLAGS = -x ./debug.gdb

BUILD_DIR = build
SRC = $(wildcard test/*.S) $(wildcard test/*.c) $(wildcard lib/*.c)
OBJ = start.o $(filter-out start.o, $(wildcard *.o))


all:
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $(SRC)
	make kernel8

kernel8:
	$(LINKER) -T test/linker.ld -o $(BUILD_DIR)/kernel8.elf $(OBJ)
	$(OBJCOPY) $(OBJCOPYFLAGS) $(BUILD_DIR)/kernel8.elf $(BUILD_DIR)/kernel8.img
	$(OD) -D $(BUILD_DIR)/kernel8.elf > $(BUILD_DIR)/kernel8.objdump
	$(OD) -x $(BUILD_DIR)/kernel8.elf > $(BUILD_DIR)/kernel8.xobjdump
	$(OD) -s $(BUILD_DIR)/kernel8.elf > $(BUILD_DIR)/kernel8.content
	rm $(OBJ)

debug:
	qemu-system-aarch64 -M raspi3b\
		-kernel $(BUILD_DIR)/kernel8.img\
		-display none\
		-serial null\
		-serial stdio\
		-S -s

run:
	qemu-system-aarch64 -M raspi3b\
		-kernel $(BUILD_DIR)/kernel8.img\
		-display none\
		-serial null\
		-serial stdio\
		-initrd initramfs.cpio
gdb:
	$(GDB) $(GDBFLAGS)

clean:
	rm -rf $(BUILD_DIR)
	rm *.o
