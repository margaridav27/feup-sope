#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[], char* env[]) {
    char* file1 = argv[1];

    FILE* fp1 = fopen(file1, "r"); 

    if (fp1 == NULL) { 
        printf("Error whilst opening the file1.\n");
    }
    else {
        char buf[1000];
        int nmemb;

        nmemb = fread(buf, 1, 1000, fp1); 

        if (argc < 3) {
            printf("%s", buf);
        }
        else {
            char* file2 = argv[2];

            FILE* fp2 = fopen(file2, "w"); 

            if (fp2 == NULL) {
                printf("Error whilst opening the file2.\n");
            }
            else {
                fwrite(buf, 1, nmemb, fp2);
            }
            
            fclose(fp2);
        }
    }

    fclose(fp1);
}