#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

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
        char msg_pt1[1024];

        read(pp[0], msg_pt1, sizeof(msg_pt1));
        close(pp[0]);

        char *msg_pt2 = "Systems";
        char *msg_final = strcat(msg_pt1, msg_pt2);

        write(pp[1], msg_final, 1+strlen(msg_final));
        close(pp[1]);
    }
    else { //parent
        write(pp[1], "Operating ", 1+strlen("Operating "));
        close(pp[1]);

        wait(NULL); // waiting for the child to finish

        char msg[1024];

        read(pp[0], msg, sizeof(msg));
        close(pp[0]);

        printf("%s\n", msg);
    }	
}
