#include "headers.h"
#include <unistd.h>

int main(int argc, char *argv[]) {
        //maskProc(argc, argv);
        
        //if(fork()!=0){return 0;}
        if(communication()==1){return -1;}
        //if(reverseConnection()==1){return -1;}
        return 0;
}



