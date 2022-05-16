all: start.o write1.exe alarm1.exe alarm2.exe alarm3.exe jmp1.exe

start.o: start.asm
	yasm -f elf64 -DYASM -D__x86_64__ -DPIC start.asm -o start.o

%.exe: %.c start.o 
	gcc -c -g -Wall -fno-stack-protector -nostdlib -I. -I.. -DUSEMINI -o tmp.o $<
	ld -m elf_x86_64 --dynamic-linker /lib64/ld-linux-x86-64.so.2 -o $@ tmp.o start.o -L. -L.. -lmini
	rm tmp.o

clean:
	rm *.o *.exe