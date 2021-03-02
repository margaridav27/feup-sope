#include <stdio.h>

int main(int argc, char* argv[], char* env[]) {
    for (int i = 0; i < 100000; i++) {
        printf("Hello World");
    }
}

/*
    on the command line:
        gcc ex10.c -o ex10
        time ./ex10
    output:
        real	0m0,276s
        user	0m0,025s
        sys	    0m0,117s
*/