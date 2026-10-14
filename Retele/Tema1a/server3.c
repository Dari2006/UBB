/*n client trimite unui server un sir de caractere. Serverul va returna clientului acest sir oglindit (caracterele sirului in ordine inversa).
 */

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(){
	int welcomeSocket, newSocket;
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;

	welcomeSocket = socket(AF_INET, SOCK_STREAM, 0);
	//memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8888);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(welcomeSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

	listen(welcomeSocket, 5);

	socklen_t addr_size = sizeof(serverStorage);

	while(1){
		newSocket = accept(welcomeSocket, (struct sockaddr*)&serverStorage, &addr_size);
		printf("m am conectat\n");
		
		int nr = 0;
		recv(newSocket, &nr, sizeof(int), 0);
		printf("am primit %d caractere\n", nr);
		
		char* buffer = malloc((nr + 1) * sizeof(char));
		
		ssize_t total = 0;
		while(total < nr){
			ssize_t n = recv(newSocket, buffer, nr * sizeof(char), 0);
			total+=n;
			if(n <= 0) break;
		}
		buffer[nr] = '\0';

		for(int i = 0; i < nr / 2; i++){
			char aux = buffer[i];
			buffer[i] = buffer[nr - i - 1];
			buffer[nr - i - 1] = aux;
		}

		send(newSocket, buffer, nr * sizeof(char), 0);
		free(buffer);

		close(newSocket);
	}

	close(welcomeSocket);
	return 0;


}
