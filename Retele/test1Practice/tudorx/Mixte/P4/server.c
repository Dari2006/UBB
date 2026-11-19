#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>

void serve(int clinet, int port){
    // Make UDP Server
    struct sockaddr_in udp_server;
    udp_server.sin_family = AF_INET;
    udp_server.sin_port = htons(port);
    udp_server.sin_addr.s_addr = INADDR_ANY;

    int udp_sock = socket(AF_INET,SOCK_DGRAM,0);

    if(bind(udp_sock,(struct sockaddr*)&udp_server,sizeof(udp_server)) == -1){
        perror("Error");
        exit(1);
    }

    int n;
    recv(clinet,&n,sizeof(n),0);
    n = ntohl(n);
    
    // Send port
    port = htonl(port);
    send(clinet,&port,sizeof(port),0);
    close(clinet);

    // UDP comms
    struct sockaddr_in udp_client;
    socklen_t size = sizeof(udp_client);

    srand(time(NULL)); 
    int cod = 1000 + rand() % 9000;

    // Defusal
    int msg[2];
    time_t start = time(NULL);
    int x;
    int k = 1;
    while(1){
        recvfrom(udp_sock,&x,sizeof(x),MSG_WAITALL,(struct sockaddr*)&udp_client,&size);
        x = ntohl(x);
        if(x == cod){
            msg[0] = 1;
            break;
        }else{
            msg[0] = 0;
        }

        if(k >= n){
            msg[0] = 2;
            break;
        }

        if(difftime(time(NULL), start) >= 60){
            msg[0] = 3;
            break;
        }

        int c = cod;
        int hint = 0;
        while(x){
            if(x % 10 == c % 10) hint++;
            x /= 10;
            c /= 10;
        }
        msg[1] = hint;

        msg[0] = htonl(msg[0]);
        msg[1] = htonl(msg[1]);

        sendto(udp_sock,&msg,sizeof(msg),0,(struct sockaddr*)&udp_client,size);
        k++;
    }   
    msg[0] = htonl(msg[0]);
    msg[1] = htonl(msg[1]);

    sendto(udp_sock,&msg,sizeof(msg),0,(struct sockaddr*)&udp_client,size);
    close(udp_sock);
}

int main(){
    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = htons(3663);
    server.sin_addr.s_addr = INADDR_ANY;

    int port = 4000;

    int serverSock = socket(AF_INET,SOCK_STREAM,0);

    if(serverSock == -1){
        perror("Error");
        return 1;
    }

    if(bind(serverSock,(struct sockaddr *) &server,sizeof(server)) == -1){
        perror("Error");
        return 1;
    }

    if(listen(serverSock,5) == -1){
        perror("Error");
        return 1;
    }

    while(1){
        int sockClinet = accept(serverSock,NULL,NULL);

        if(sockClinet == -1){
            perror("Error");
            return 1;
        }

        if(fork() == 0){
            close(serverSock);
            serve(sockClinet, port);
            exit(0);
        }else{
            close(sockClinet);
        }
        port++;
    }
    return 0;
}