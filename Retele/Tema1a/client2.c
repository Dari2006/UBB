#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
int main(){
	int clientSocket;
	
	struct sockaddr_in serverAddr;

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8888);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	printf("conectat\n");
	printf("sir: ");

	char text[1028];
	
	fgets(text, sizeof(text), stdin);
	printf("am citit textul\n");
	int nr = strlen(text);
	printf("trimit %d\n", nr);
	ssize_t total = 0;
	send(clientSocket, &nr, sizeof(int), 0);
	while(total < nr){
		ssize_t n = send(clientSocket, text, nr, 0);
		if(n <= 0) break;
		total+=n;
	}
int k;
	recv(clientSocket, &k, sizeof(int),0);
	printf("am primit %d", k);
	printf("\n");
	close(clientSocket);
	
	return 0;
}
