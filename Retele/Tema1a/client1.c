#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){
	int clientSocket, nr, size;
	struct sockaddr_in serverAddr;
	//creeaza sokcetul clientului
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8888);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//conecteaza sokecutl cu adresa
	connect(clientSocket, (struct sockaddr*) &serverAddr, sizeof serverAddr);
	
	int rez, n;
	printf("nr de numere: ");
	scanf("%d", &nr);
	send(clientSocket, &nr, sizeof(int),0);
	printf("\n");
	printf("numere: ");
	for(int i = 0; i < nr; i++){
		scanf("%d", &n);
		send(clientSocket, &n, sizeof(int),0);
	}

	recv(clientSocket, &rez, sizeof(int), 0);
	printf("%d", rez);
	close(clientSocket);
}
