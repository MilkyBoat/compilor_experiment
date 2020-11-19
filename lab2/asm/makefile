.PHONY: asm, my, clean

default:
	cc -O0 -m32 -o main.out main.c

asm:
	cc -O0 -m32 -S -o main.S main.c

my:
	cc -O0 -m32-march=i386 -o mymain.out mymain.S
	qemu-i386 mymain.out

clean:
	-rm *.out
