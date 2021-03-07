#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pp1[2];
    int pp2[2];
    int pid;

    if (pipe(pp1) == -1 || pipe(pp2) == -1) { 
        perror("Failed to create pipe.\n");
        exit(1); 
    }

    if ((pid = fork()) == -1) { 
        perror("Failed to fork process.\n");
        exit(2);
    }
    
    if (pid == 0) { //child
        char msg_pt1[1024];

        close(pp1[1]);
        read(pp1[0], msg_pt1, sizeof(msg_pt1));
        close(pp1[0]);

        char *msg_pt2 = "Systems";
        char *msg_final = strcat(msg_pt1, msg_pt2);

        close(pp2[0]);
        write(pp2[1], msg_final, 1+strlen(msg_final));
        close(pp2[1]);
    }
    else { //parent
        close(pp1[0]);
        write(pp1[1], "Operating ", 1+strlen("Operating "));
        close(pp1[1]);

        char msg[1024];

        close(pp2[1]);
        read(pp2[0], msg, sizeof(msg));
        close(pp2[0]);

        printf("%s\n", msg);
    }	
}
