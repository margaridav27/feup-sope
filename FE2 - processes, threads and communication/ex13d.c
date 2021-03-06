#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

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
        char msg_pt1[1024];

        while ((np = open(path, O_RDWR)) < 0) { }    
        read(np, msg_pt1, sizeof(msg_pt1));

        char *msg_pt2 = "Systems";
        char *msg_final = strcat(msg_pt1, msg_pt2);

        write(np, msg_final, 1+strlen(msg_final));
        close(np);
    }
    else { //parent
        int np;
        char msg[1024];

        while ((np = open(path, O_RDWR)) < 0) { }  
        write(np, "Operating ", 1+strlen("Operating "));
  
        wait(NULL); // waiting for the child to finish

        read(np, msg, sizeof(msg));
        close(np);

        printf("%s\n", msg);    
    }	
}
