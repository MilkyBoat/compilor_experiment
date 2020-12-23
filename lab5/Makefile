CC := g++
CFLAGS := -Wall -Wextra -std=c++11  # without debug
TARGET := ./bin/main

all: run

src/main.l.yy.c: src/main.l
	 flex --noyywrap -o src/main.l.yy.cpp  src/main.l

src/main.tab.c: src/main.y
	bison -o src/main.tab.cpp --defines=src/main.tab.h -v src/main.y

src/pch.h.gch: src/pch.h
	g++ -x c++-header -o src/pch.h.gch -c src/pch.h

lex: src/main.l.yy.c

yacc: src/main.tab.c

main: src/pch.h.gch
	$(CC) $(CFLAGS) $(shell ls ./src/*.cpp) -o ./bin/main

.PHONY: all clean main run lex yacc test 1 2 3 debug link testscope asm nasm example-code out

run: lex yacc main

clean:
	rm -f src/*.output src/main.l.yy.cpp src/main.tab.cpp src/main.tab.h src/main.output src/pch.h.gch $(TARGET) *.o ./bin/* 

test: lex yacc main
	./bin/main tests/test.c > result.txt

1: lex yacc main
	./bin/main tests/1.c > result.txt

2: lex yacc main
	./bin/main tests/2.c > result.txt

3: lex yacc main
	./bin/main tests/3.c > result.txt
