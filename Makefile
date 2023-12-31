CC = aarch64-linux-gnu-gcc
LINKER = aarch64-linux-gnu-ld
OBJ_CPY = aarch64-linux-gnu-objcopy

all: kernel8.img

a.o: a.S
	${CC} -c a.S -o a.o

kernel8.img: a.o $(OBJS)
	$(LINKER) a.o -T linker.ld -o kernel8.elf
	$(OBJ_CPY) -O binary kernel8.elf kernel8.img

clean:
	rm a.o
	rm kernel8.elf
	rm kernel8.img

run:
	qemu-system-aarch64 -M raspi3b -kernel kernel8.img -display none -d in_asm
