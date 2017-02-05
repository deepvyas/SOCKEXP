#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
char out_buff[1024];
char in_buff[1024];

int main(int argc, char* argv[]){
	int socketfd,newsocket;
	struct sockaddr_in serverAddr,cliAddr;
	socklen_t cli_size;
	socketfd =socket(PF_INET,SOCK_STREAM,0);
	bzero((char *)&serverAddr,sizeof serverAddr);
	serverAddr.sin_family = AF_INET;
	if(argc<2) fprintf(stderr,"No port provided");
	serverAddr.sin_port = htons(atoi(argv[1]));
	serverAddr.sin_addr.s_addr= INADDR_ANY;

	if(bind(socketfd,(struct sockaddr*)&serverAddr,sizeof serverAddr)<0){
		fprintf(stderr,"Error binding socket");
		exit(1);
	}

	listen(socketfd,1);
	cli_size = sizeof cliAddr;
	newsocket = accept(socketfd,(struct sockaddr*)&cliAddr,&cli_size);
	if(newsocket<0){
		fprintf(stderr,"Error in accepting connection");
		exit(1);
	}
	//Guessing game;
	int randomint=123,guessedint,correct=0;
	int n;
	while(correct!=1){
		bzero(in_buff,sizeof in_buff);
		n=read(newsocket,in_buff,sizeof in_buff);
		if(n<0){
			fprintf(stderr,"Read Error");
			exit(1);
		}
		printf("Input Buffer: %s",in_buff);
		guessedint = atoi(in_buff);
		bzero(out_buff,sizeof out_buff);
		if(guessedint>randomint){
			strcpy(out_buff,"L");
		}
		else if(guessedint<randomint){
			strcpy(out_buff,"H");
		}
		else{
			strcpy(out_buff,"O");
		}

		n=write(newsocket,out_buff,sizeof out_buff);
		if(n<0){
			fprintf(stderr,"Error Writing");
		}

	}
	close(newsocket);
	close(socketfd);
	return 0;
}
