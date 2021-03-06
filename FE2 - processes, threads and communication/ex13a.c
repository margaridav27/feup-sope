#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pp[2];
    int pid;

    if (pipe(pp) == -1) { 
        perror("Failed to create pipe.\n");
        exit(1); 
    }

    if ((pid = fork()) == -1) { 
        perror("Failed to fork process.\n");
        exit(2);
    }
    
    if (pid == 0) { //child
        char msg[1024];
        close(pp[1]);
        read(pp[0], msg, sizeof(msg));
        close(pp[0]);

        char *msg_pt2 = "Systems";
        char *msg_final = strcat(msg, msg_pt2);

        printf("%s\n", msg_final);    
    }
    else { //parent
        close(pp[0]);
        write(pp[1], "Operating ", 1+strlen("Operating "));
        close(pp[1]);
    }	
}
