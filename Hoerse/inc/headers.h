#ifndef HEADERS_H
#define HEADERS_H

int openPort();
int sendUpdate();
void redirection(int connID);
void mainMenu(int connID);

#define TARGET_IP "192.168.68.107"
#define TARGET_PORT 8080

#define ATTACKER_IP "192.168.68.100"
#define ATTACKER_PORT 4444

#endif
