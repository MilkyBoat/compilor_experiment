.PHONY: pre, ast, ir, asm, obj, exe, antiobj, antiexe

default:
	cc -O0 -o simple.out simple.c

pre:
	cc -E -o simple.i simple.c

# 生成`simple.c.003t.original`
ast:
	cc -fdump-tree-original-raw simple.c

# 会生成多个阶段的文件 (.dot)，可以被 graphviz 可视化，可以直接使用 vscode 插件
# (Graphviz (dot) language support for Visual Studio Code)。
# 此时的可读性还很强。`simple.c.011t.cfg.dot`
cfg:
	cc -O0 -fdump-tree-all-graph simple.c

# 此时可读性不好，简要了解各阶段更迭过程即可。
ir:
	cc -O0 -fdump-rtl-all-graph simple.c

asm:
	cc -O0 -S -masm=att -o simple.S simple.i

obj:
	cc -O0 -c -o simple.o simple.S

antiobj:
	objdump -d simple.o > simple-anti-obj.S
	nm simple.o > simple-nm-obj.txt

exe:
	cc -O0 -o simple.out simple.o

antiexe:
	objdump -d simple.out > simple-anti-exe.S
	nm simple.out > simple-nm-exe.txt

clean:
	-rm *.c.*

clean-all:
	-rm *.c.* *.o *.S *.i *.dot *.out *.txt
