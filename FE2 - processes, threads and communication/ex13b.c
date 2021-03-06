#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main() {
    int pid;
    char *path = "my_np";
        
    if (mkfifo(path, 0666) < 0) {
        perror("Failed to create name pipe.\n");
        exit(1);
    }

    if ((pid = fork()) == -1) { 
        perror("Failed to fork process.\n");
        exit(2);
    }
    
    if (pid == 0) { //child
        int np;

        while ((np = open(path, O_WRONLY)) < 0) { }    
        write(np, "Operating ", 1+strlen("Operating "));
        close(np);
    }
    else { //parent
        int np;
        char msg[1024];

        while ((np = open(path, O_RDONLY)) < 0) { }    
        read(np, msg, sizeof(msg));
        close(np);

        char *msg_pt2 = "Systems";
        char *msg_final = strcat(msg, msg_pt2);

        printf("%s\n", msg_final); 
    }	
}
