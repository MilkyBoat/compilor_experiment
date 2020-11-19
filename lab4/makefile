.PHONY: lc, lcc, lcfp, lccfp, lcfp, lccfp, clean
lc:
	flex sysy.l
	gcc lex.yy.c -o lc.out
	./lc.out
lcc:
	flex -+ sysycc.l
	g++ lex.yy.cc -o lcc.out
	./lcc.out
lcf:
	flex sysy.l
	gcc lex.yy.c -o lcf.out
	./lcf.out <testin
lccf:
	flex -+ sysycc.l
	g++ lex.yy.cc -o lccf.out
	./lccf.out <testin
lcpf:
	flex sysy.l
	gcc lex.yy.c -o lcfp.out
	./lcfp.out <testin_plus
lccpf:
	flex -+ sysycc.l
	g++ lex.yy.cc -o lccfp.out
	./lccfp.out <testin_plus
clean:
	rm *.out
