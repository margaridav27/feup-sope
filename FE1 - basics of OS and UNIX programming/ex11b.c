#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[], char* env[]) {
    char* file1 = argv[1];
    char* file2 = argv[2];

    FILE* fp1 = fopen(file1, "r"); //file pointer of file1
    FILE* fp2 = fopen(file2, "w"); //file pointer of file2  

    char* buf[1000];
    int nmemb;

    if (fp1 == NULL) { //fopen returns NULL upon failure
        printf("Error whilst opening the file1.\n");
    }
    else if (fp2 == NULL) {
        printf("Error whilst opening the file2.\n");
    }
    else {
        nmemb = fread(buf, 1, 1000, fp1); //returns the number of elements actually read
        fwrite(buf, 1, nmemb, fp2);
    }
    
    fclose(fp1);
    fclose(fp2);
}