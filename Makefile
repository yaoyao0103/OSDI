CC = aarch64-linux-gnu-gcc
LINKER = aarch64-linux-gnu-ld
OBJ_CPY = aarch64-linux-gnu-objcopy

all: 
	$(CC) -g -c start.S -o start.o
	make kernel8
kernel8: start.o $(OBJS)
	$(LINKER)  start.o -T linker.ld -o kernel8.elf
	$(OBJ_CPY) -O binary kernel8.elf kernel8.img

clean:
	rm a.o
	rm kernel8.elf
	rm kernel8.img

run:
	qemu-system-aarch64 -M raspi3b -kernel kernel8.img -display none -d in_asm
