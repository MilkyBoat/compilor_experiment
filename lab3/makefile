
operator:
	bison -d operator.y
	gcc -o operator.out operator.tab.c

expr:
	bison -d expr.y
	gcc -o expr.out expr.tab.c

clean:
	-rm -f *.c *.h *.out operator expr
