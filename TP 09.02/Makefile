all: hello hello.stat hello.asm hello.prec

hello: hello.c
    cc -Wall -o hello hello.c
hello.stat: hello.c
    cc -Wall -static -o hello.stat hello.c 
hello.asm: hello.c
    cc -Wall -S -o hello.asm hello.c 
hello.prec: hello.c 
    cc -Wall -E -o hello.prec hello.c
clean:
    rm -f hello hello.stat hello.asm hello.prec