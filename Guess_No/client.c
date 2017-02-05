#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

char in_buff[1024];
char out_buff[1024];
int main(int argc,char *argv[]){
	int socketfd;
	struct sockaddr_in serverAddr;
	socklen_t addr_size;

	socketfd= socket(PF_INET,SOCK_STREAM,0);
	bzero((char *)&serverAddr,sizeof serverAddr);
	serverAddr.sin_family=AF_INET;
	if(argc<2) fprintf(stderr,"No port provided");
	serverAddr.sin_port= htons(atoi(argv[1]));
	serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");

	if(connect(socketfd,(struct sockaddr*)&serverAddr,sizeof serverAddr)<0){
		fprintf(stderr,"Connect error");
		exit(1);
	}

	int correct=0,n;
	while(correct!=1){
		printf("Guess :");
		bzero(out_buff,sizeof out_buff);
		fgets(out_buff,sizeof out_buff,stdin);
		n = write(socketfd,out_buff,sizeof out_buff);
		if(n<0){
			fprintf(stderr,"Error in writing");
			exit(1);
		}
		bzero(in_buff,sizeof in_buff);
		n= read(socketfd,in_buff,sizeof in_buff);
		if(n<0){
			fprintf(stderr,"Error in Reading");

		}
		if(strncmp(&in_buff[0],"L",1)==0){
			printf("Lower\n");
		}
		else if(strncmp(&in_buff[0],"H",1)==0){
			printf("Higher\n");
		}
		else{
			printf("Well Done!!\n");
			correct=1;
		}
	}	
	return 0;
}

