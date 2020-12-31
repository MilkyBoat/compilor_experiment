CC := g++
CFLAGS := -Wall -Wextra -std=c++11 -g
TARGET := ./main.out

.PHONY: all clean main run lex yacc test debug link testscope asm asmc nasm example-code out mytest

all: complier

src/pch.h.gch: src/pch.h
	g++ -x c++-header -o src/pch.h.gch -c src/pch.h

lex:
	flex --noyywrap -o src/lexer.cpp src/lexer.l

yacc:
	bison -o src/parser.cpp --defines=src/parser.h -v src/parser.y

main: src/pch.h.gch
	$(CC) $(CFLAGS) $(shell ls ./src/*.cpp) -o $(TARGET)

complier: lex yacc main

run: complier
	./test.out

l1:
	./test.out --level 1

l2:
	./test.out --level 2

l3:
	./test.out --level 3

l4:
	./test.out --level 4

diffcheck:
	./test.out --diffcheck
	
noerrlog:
	./test.out --nolog

type:
	./test.out --type

asm:
	gcc -S asmTest.c -m32 -o asmTest.s

asmc:
	gcc asmTest.s -m32 -o asmTest.out
	qemu-i386 asmTest.out

st: 
	./main.out test/4/02_path.c > asmTest.s
	gcc asmTest.s -m32 -o asmTest.out
	qemu-i386 asmTest.out

std:
	for file in $(basename $(shell find test/?/*.c)); \
	do \
		touch -a $$file.in; \
	done

different:
	for file in $(basename $(shell find test/?/*.c)); \
	do \
		cp -u $$file.c $$file.sy; \
	done

clean:
	rm -f src/lexer.cpp src/parser.cpp src/parser.h src/pch.h.gch $(TARGET) *.o ./bin/*
	rm -f src/*.output
	rm -rf test/*/*.out test/*/*.output

clean-complete:clean
	rm -rf test/*/*.s test/*/*.res test/*/*.sy test/*/*.output
