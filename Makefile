SRCS = $(wildcard test/*.c) $(wildcard test/*.S) $(wildcard lib/*.c)
OBJS = $(wildcard *.o)
CFLAGS = -Ilib -Itest -Wall -ffreestanding -nostdinc -nostdlib -nostartfiles
CC = aarch64-linux-gnu-gcc
LINKER = aarch64-linux-gnu-ld
OBJCOPY = aarch64-linux-gnu-objcopy
OD = aarch64-linux-gnu-objdump

GDB = aarch-gdb
GDBFLAGS = -x ./debug.gdb

BUILD_DIR = build

all:
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -g $(SRCS)
	make kernel8

kernel8:
	$(LINKER) $(OBJS) -T lib/linker.ld -o $(BUILD_DIR)/kernel8.elf
	$(OBJCOPY) -O binary $(BUILD_DIR)/kernel8.elf $(BUILD_DIR)/kernel8.img
	$(OD) -D $(BUILD_DIR)/kernel8.elf > $(BUILD_DIR)/kernel8.objdump
	$(OD) -x $(BUILD_DIR)/kernel8.elf > $(BUILD_DIR)/kernel8.xobjdump
	$(OD) -s $(BUILD_DIR)/kernel8.elf > $(BUILD_DIR)/kernel8.content
	rm $(OBJS)
clean:
	rm -rf $(BUILD_DIR)
	rm $(OBJS)
run:
	qemu-system-aarch64 -M raspi3b -kernel $(BUILD_DIR)/kernel8.img -serial null -serial stdio

debug: 
	qemu-system-aarch64 -M raspi3b -kernel $(BUILD_DIR)/kernel8.img -serial
	null -serial stdio -S -s

gdb: $(GDB) $(GDBFLAGS)