#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

void serve(int clinet, int port){
    // Authentication
    int n;
    char username[100], password[100];
    recv(clinet,&n,sizeof(n),MSG_WAITALL);
    n = ntohl(n);
    recv(clinet,username,n,MSG_WAITALL);
    username[n] = '\0';
    recv(clinet,&n,sizeof(n),MSG_WAITALL);
    n = ntohl(n);
    recv(clinet,password,n,MSG_WAITALL);
    password[n] = '\0';

    if(strcmp(username,"admin") == 0 && strcmp(password,"1234") == 0){
        // UDP
        struct sockaddr_in udp;
        udp.sin_family = AF_INET;
        udp.sin_port = htons(port);
        udp.sin_addr.s_addr = INADDR_ANY;

        int udpSock = socket(AF_INET,SOCK_DGRAM,0);

        if(bind(udpSock,(struct sockaddr *) &udp,sizeof(udp)) == -1){
            perror("Error");
            exit(1);
        }
        
        // Comunicare cu UDP
        int status = port;
        status = htonl(status);
        send(clinet,&status,sizeof(int),0);
        close(clinet);

        struct sockaddr_in client;
        socklen_t len = sizeof(client);

        int x;
        recvfrom(udpSock,&n,sizeof(n),MSG_WAITALL,(struct sockaddr*)&client,&len);
        n = ntohl(n);
        recvfrom(udpSock,&x,sizeof(x),MSG_WAITALL,(struct sockaddr*)&client,&len);
        x = ntohl(x);
        int min = x;
        int max = x;
        for(int i = 1; i < n; i++){
            recvfrom(udpSock,&x,sizeof(x),MSG_WAITALL,(struct sockaddr*)&client,&len);
            x = ntohl(x);
            printf("%d ",x);
            if(max < x) max = x;
            if(min > x) min = x;
        }

        min = htonl(min);
        max = htonl(max);
        sendto(udpSock,&min,sizeof(min),0,(struct sockaddr*)&client,len);
        sendto(udpSock,&max,sizeof(max),0,(struct sockaddr*)&client,len);
        return;
    }

    int status = 403;
    status = htonl(status);
    send(clinet,&status,sizeof(int),0);
    close(clinet);
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