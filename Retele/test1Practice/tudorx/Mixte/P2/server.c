#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


void serve(int client_socket, int port){
    int n;
    recv(client_socket,&n,sizeof(n),MSG_WAITALL);
    n = ntohl(n);

    // Server UDP
    struct sockaddr_in udp;
    udp.sin_family = AF_INET;
    udp.sin_port = htons(port);
    udp.sin_addr.s_addr = INADDR_ANY;

    int sockUDP = socket(AF_INET,SOCK_DGRAM,0);

    if(bind(sockUDP,(struct sockaddr*)&udp,sizeof(udp)) == -1){
        port = 403;
        port = htonl(port);
        send(client_socket,&port,sizeof(port),0);
        perror("Error");
        exit(1);
    }

    // Sneding Port
    port = htonl(port);
    send(client_socket,&port,sizeof(port),0);

    close(client_socket);

    // Comms in UDP
    struct sockaddr_in client;
    socklen_t len = sizeof(client);

    n = abs(n);
    int request[3];
    // Operations
    while(n){
        recvfrom(sockUDP,request,sizeof(request),MSG_WAITALL,(struct sockaddr*)&client,&len);

        for(int i = 0; i < 3; i++){
            request[i] = ntohl(request[i]);
        }        

        int rez[2] = {0,0};
        switch (request[0])
        {
        case 1:
            rez[1] = request[1] + request[2];
            break;
        case 2:
            rez[1] = request[1] - request[2];
            break;
        case 3:
            rez[1] = request[1] * request[2];
            break;
        case 4:
            if(request[2] == 0){
                rez[0] = 2;
                break;
            }
            rez[1] = request[1] / request[2];
            break;
        
        default:
            rez[0] = 1;
            break;
        }

        rez[0] = htonl(rez[0]);
        rez[1] = htonl(rez[1]);
        sendto(sockUDP,rez,sizeof(rez),0,(struct sockaddr*)&client,len);
        n--;
    }
    close(sockUDP);
}


int main(){
    signal(SIGCHLD, SIG_IGN);

    struct sockaddr_in server;

    int server_sock = socket(AF_INET,SOCK_STREAM,0);

    int port = 4000;

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
        int client_sock = accept(server_sock,NULL,NULL);

        if(client_sock == -1){
            perror("Client");
            return 1;
        }

        if(fork() == 0){
            close(server_sock);
            serve(client_sock,port);
            exit(0);
        }else {
            close(client_sock);
        }

        port++;
    }

    return 0;
}