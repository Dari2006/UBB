#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main(){
	int clientSocket;
	struct sockaddr_in serverAddr;
	
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8888); 
	serverAddr.sin_addr.s_addr = inet_addr("192.168.40.143");
	
	if(connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0){
   		 perror("connect");
   		 return 1;
	}
	printf("conectat\n");
	
	char buf[]="67lubenite";
	int nr = 67;
	//scanf("%d", &nr);
//	char n = stoi(nr);
	send(clientSocket, &nr, sizeof(nr), 0);
	printf("am triimis");
	int rez;
	recv(clientSocket, &rez, sizeof(rez), 0);
	printf("%d", rez);
	close(clientSocket);
	return 0;
}

