#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main(){
	int clientSocket;
	struct sockaddr_in serverAddr;

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8888);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	printf("m am conectat la sv\n");

	printf("sir: ");
	char text[1028];

	fgets(text, sizeof(text), stdin);

	int nr = strlen(text);
	printf("\ntrimit %d caractere\n", nr);
	ssize_t total = 0;
	send(clientSocket, &nr, sizeof(int), 0);
	while(total < nr){
		ssize_t n = send(clientSocket, text, nr, 0);
		if(n <= 0){
			break;
		}
		total+=n;
	}

	recv(clientSocket, text, nr * sizeof(char), 0);
	printf("am primit %ld caratere\n", strlen(text));
	printf("%s", text);
	printf("\n");
	return 0;
}


