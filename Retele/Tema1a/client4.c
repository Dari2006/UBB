#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){

	int c;
	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8888);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	c = socket(AF_INET, SOCK_STREAM, 0);
	if(c < 0){
		perror("eroare la socket");
		exit(1);
	}

	if(connect(c, (struct *sockaddr)&serverAddr, sizeof(serverAddr)) < 0){
		perror("eroare la binf");
		exit(1);
	}
	printf("conectat\n");
	char text1[1028], text2[1028];
	printf("text1: ");
	scanf(text1, stdin, sizeof(text1));
	getchar();
	printf("text2: ");
	scanf(text2, stdin, sizeof(text2));
	int nr1 = strlen(text1);
	int nr2 = strlen(text2);

	text1[nr1] = '\0';
	text2[nr2] = '\0';

	send(c, &nr1, sizeof(nr1), 0);
	send(c, text1, nr1, 0);
	send(c, &nr2, sizeof(nr2), 0);
	send(c, text2, nr2,0);
	char buffer[1028];
	recv(c, buffer, sizeof(buffer), 0);
	printf("%s", buffer);
	close(c);
	return 0;
}
