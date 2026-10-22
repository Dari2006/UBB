#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void serve_client(int newSocket, uint16_t nr, uint16_t r){
	uint16_t incercari, length = 0;

	char MIC[]="mai mic";
	char MARE[]="mai mare";
	char egal[] = "egal";

	while(nr != r){
		printtf("inainte de recv\n");
		recv(newSocket, &nr, sizeof(nr),0);

		if(nr < r){
			length = htons(strlen(MIC));
			printf("trimit %hu,%s\n", strlen(MIC), mic);
			send(newSocket, &length, sizeof(length), 0);
			send(newSocket, MIC, length * sizeof(char), 0);
		
		incercari++;
	}



}
