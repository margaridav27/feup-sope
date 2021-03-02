#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char* argv[], char* env[]) {
    if (argc == 1) {
        printf("No arguments.\n");
    }
    else {
        int val = open(argv[1], O_RDONLY);

        if (val == -1) {
            // a) output encaminhado para trace.txt
            printf("Error no. %d!\n", errno); 

            // b) output encaminhado para errors.txt
            fprintf(stderr, "Error no. %d!\n", errno); 
            perror("Error");
        }
    }
}