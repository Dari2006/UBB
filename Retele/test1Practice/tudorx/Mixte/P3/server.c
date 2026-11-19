#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


void serve(int client_sock_1, int client_sock_2){
    int status;
    status = 200;
    status = htonl(status);
    send(client_sock_1,&status,sizeof(status),0);

    status = 500;
    status = htonl(status);
    send(client_sock_2,&status,sizeof(status),0);

    int port;
    recv(client_sock_1,&port,sizeof(port),MSG_WAITALL);
    send(client_sock_2,&port,sizeof(port),0);

    recv(client_sock_2,&port,sizeof(port),MSG_WAITALL);
    send(client_sock_1,&port,sizeof(port),0);
    
    close(client_sock_1);
    close(client_sock_2);
}


int main(){
    signal(SIGCHLD, SIG_IGN);

    struct sockaddr_in server;

    int server_sock = socket(AF_INET,SOCK_STREAM,0);

    if(server_sock == -1){
        perror("Socket");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(3663);
    server.sin_addr.s_addr = INADDR_ANY;

    if(bind(server_sock,(struct sockaddr*) &server,sizeof(server)) == -1){
        perror("Bind");
        return 1;
    }

    if(listen(server_sock,5) == -1){
        perror("Listen");
        return 1;
    }

    // Deservire Clienti
    while(1){
        int client_sock_1 = accept(server_sock,NULL,NULL);
        if(client_sock_1 == -1){
            perror("Client");
            return 1;
        }

        int client_sock_2 = accept(server_sock,NULL,NULL);
        if(client_sock_2 == -1){
            perror("Client");
            return 1;
        }

        if(fork() == 0){
            close(server_sock);
            serve(client_sock_1, client_sock_2);
            exit(0);
        }else {
            close(client_sock_1);
            close(client_sock_2);
        }
    }

    return 0;
}