#include "headers.h"
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

void mainMenu(int connID){
    char buffer[1024];
    memset(buffer, 0, 1024);
    int RUN = 1;
    int bytes_read;
    char *hello;
    
    while(RUN){
            bytes_read = read(connID, buffer, 1024);
            
            if (bytes_read == 0) {
                 printf("[!] Peer disconnected (EOF). Exiting menu.\n");
                 RUN = 0;
                 break; 
             }else if (bytes_read < 0) {
                 perror("[!] Read error");
                 RUN = 0;
                 break;
             }
           
            printf("Client sent: %s\n", buffer);
        
            if (strcmp(buffer, "rs") == 0) {
                  printf("starting rs\n");
                  redirection(connID);
            }else if (strcmp(buffer, "exit") == 0) {
                  printf("Exit command received. Shutting down...\n");
                  
                  hello = "Exiting...";
                  safeSend(connID, hello);
                  //send(connID, hello, strlen(hello), 0);
                  
                  RUN = 0;
                  continue;
            }else{
                  memset(buffer, 0, 1024);
            }
        }
}
