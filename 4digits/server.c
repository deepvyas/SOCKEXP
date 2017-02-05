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
	if(argc<3) fprintf(stderr,"No port provided or No number provided");
	serverAddr.sin_port = htons(atoi(argv[1]));
	serverAddr.sin_addr.s_addr= INADDR_ANY;

	if(bind(socketfd,(struct sockaddr*)&serverAddr,sizeof serverAddr)<0){
		fprintf(stderr,"Error binding socket");
		exit(1);
	}
	int cnt=0;
	while(listen(socketfd,5)==0){
		cli_size = sizeof cliAddr;
		newsocket = accept(socketfd,(struct sockaddr*)&cliAddr,&cli_size);
		cnt++;
		printf("Client No. %d. SocketFD : %d\n",cnt,newsocket);
		if(newsocket<0){
			fprintf(stderr,"Error in accepting connection");
			exit(1);
		}
		int pid=fork();
		if(pid==0){
			int randomint=atoi(argv[2]),guessedint,correct=0;
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
				int bull=0,cows=0;
				int temp1=guessedint,temp2=randomint;
				int vis[10];
				bzero(vis,sizeof vis);
				int i=0;
				for(i=0;i<4;i++){
					vis[temp1%10]=1;
					if(temp1%10==temp2%10) bull++;
					temp1/=10;
					temp2/=10;
				}
				temp1=guessedint,temp2=randomint;
				for(i=0;i<4;i++){
					if(vis[temp2%10]&&temp1%10!=temp2%10){
						cows++;
					}
					temp1/=10;
					temp2/=10;
				}
				/*if(guessedint>randomint){
					strcpy(out_buff,"L");
				}
				else if(guessedint<randomint){
					strcpy(out_buff,"H");
				}
				else{
					strcpy(out_buff,"O");
					correct=1;
				}*/
				if(bull==4){
					sprintf(out_buff,"O",cows,bull);
				}
				else{
					sprintf(out_buff,"%dC%dB",cows,bull);
				}
				n=write(newsocket,out_buff,sizeof out_buff);
				if(n<0){
					fprintf(stderr,"Error Writing");
					exit(0);
				}
				sleep(1);
			}
			close(newsocket);
			break;
		}
		else{
			if(pid<0){
				fprintf(stderr,"Error Forking");
				exit(1);
			}
			close(newsocket);
		}
	}
	close(socketfd);
	return 0;
}
