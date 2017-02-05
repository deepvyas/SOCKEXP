#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
char buffer[1024];
int main(){
	int welcomeSocket,newSocket;
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;

	welcomeSocket = socket(PF_INET,SOCK_STREAM,0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(7891);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(serverAddr.sin_zero,'\0',sizeof serverAddr.sin_zero);

	bind(welcomeSocket,(struct sockaddr *)&serverAddr,sizeof serverAddr);

	if(listen(welcomeSocket,5)==0){
		printf("Listening:\n");
	}
	else
		printf("More than limit Error!!\n");

	addr_size = sizeof serverStorage;

	newSocket = accept(welcomeSocket,
			(struct sockaddr *)&serverStorage,&addr_size);
	memset(buffer,0,sizeof buffer);
	strcpy(buffer,"Output from server\n you were successfully able to send and receive message\n");
	send(newSocket,buffer,150,0);
	return 0;
}

	
