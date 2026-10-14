#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/in.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int main(){
	int welcomeSocket, newSocket,nr1,nr2;
	struct sockaddr_in server, client;
	struct sockaddr_storage storage;

	welcomeSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(welcomeSocket < 0){
		perror("eroare la creare socket server");
		exit(1);
	}
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(8888);
	server.sin_addr.s_addr = INADDR_ANY;

	if(bind(welcomeSocket, (struct sockaddr*)&server, sizeof(server)) < 0){
		perror("eroare la bind");
		exit(1);
	}

	listen(welcomeSocket, 5);
	int c;
	socklen_t l = sizeof(client);
	while(1){
		c = accept(welcomeSocket, (struct sockaddr*)&client, &l);
		if(c < 0){
			perror("eroare la accept");
			exit(1);
		}
		printf("avem client");

		recv(c, &nr1, sizeof(nr1), 0);
		char buffer1[1028];
		int total = 0;
		while(total < nr1){
			int n = recv(c, buffer1, sizeof(buffer1), 0);
			if(n <= 0)
				break;
			total+=n;
		}
		buffer1[nr1] = '\0';

		recv(c, &nr2, sizeof(nr2), 0);

		char buffer2[1028];
		total = 0;
		while(total < nr2){
			int n = recv(c, buffer2, sizeof(buffer2), 0);
			if(n <= 0)
				break;
			total+= n;
		}

		char rez[nr1 + nr2 + 1];
		int i = 0, j = 0, k = 0;
		while(i < nr1 && j < nr2){
			if(buffer1[i] < buffer2[j]){
				rez[k++] = buffer1[i++];

			}
			else{
				rez[k++] = buffer2[j++];
			}			
		}
		rez[k] = '\0';
		send(c, &k, sizeof(k), 0);
		send(c, rez, k, 0);
		close(c);
		
	}
	close(welcomeSocket);
	return 0;
}


