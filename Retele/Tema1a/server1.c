//enunt: Un client trimite unui server un sir de numere. Serverul va returna clientului suma numerelor primite.
 
#include <stdio.h>  //fctii standard
#include <sys/socket.h> //fctii precum bind, recv, send, lsiten... constante: AF_INET, SOCK_STREAM
#include <netinet/in.h> //structuri pt adrese ip si porturiex: struct sock_addr are adresa serverului
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
int main(){
	int welcomeSocket, newSocket, nr = 0, rez;
	//int* list;
	//socketul sv         |---socket client
	int buffer;//zona in care primesti/trimit date
	struct sockaddr_in serverAddr;//adresa sv, are IP, port
	struct sockaddr_storage serverStorage;//nume confuz, aici e adresa clientului
	socklen_t addr_size;  //dimensiunea adresei
	
	welcomeSocket = socket(AF_INET, SOCK_STREAM, 0);

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8888);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	bind(welcomeSocket,
		(struct sockaddr *)&serverAddr,
		sizeof(serverAddr));

	listen(welcomeSocket, 5);
	addr_size = sizeof(serverStorage);	
	while(1){
		if(newSocket = accept(welcomeSocket, (struct sockaddr*)&serverStorage, &addr_size)<0){
			perror("nun e conect");
			exit(1);
		}
		printf("conectat");
		
		recv(newSocket, &nr, sizeof(int), 0);
		printf("am primit");
		//list = malloc(nr * sizeof(int));
		rez = 0;
		//for(int i = 0; i < nr; i++){
		//	recv(newSocket, &buffer, sizeof(int),0);
		//	rez+=buffer;
	//	}
		send(newSocket, &nr, sizeof(int), 0);
		close(newSocket);
	}	
	close(welcomeSocket);
	return 0;

}

