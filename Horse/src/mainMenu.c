#include "headers.h"
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

void mainMenu(int connID){
    char buffer[1024];
    memset(buffer, 0, 1024);
    int RUN =1;
    char *hello;
    
    while(RUN){
            read(connID, buffer, 1024);
            printf("Client sent: %s\n", buffer);
        
            if (strcmp(buffer, "rs") == 0) {
                  printf("starting rs\n");
                  redirection(connID);
            }else if (strcmp(buffer, "exit") == 0) {
                  printf("Exit command received. Shutting down...\n");
                  hello = "Exiting...";
                  send(connID, hello, strlen(hello), 0);
                  RUN = 0;
                  continue;
            }else{
                  memset(buffer, 0, 1024);
            }
        }
}
