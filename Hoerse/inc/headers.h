#ifndef HEADERS_H
#define HEADERS_H

int openPort();
int sendUpdate();
void redirection();

#define TARGET_IP "10.0.0.14"
#define TARGET_PORT 8080

#define ATTACKER_IP "10.0.0.8"
#define ATTACKER_PORT 4444

#endif
