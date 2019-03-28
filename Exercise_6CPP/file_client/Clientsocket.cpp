#include "Clientsocket.h"
#include "stdlib.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iknlib.h>
#include <arpa/inet.h>
#include <netdb.h>

using namespace std;

Clientsocket::Clientsocket(char* target_ip, int portno,int servertype)
{
    /*Defintions*/
    cout << "Initializing variables.." << endl;
    server_ = gethostbyname(target_ip);
    sockettype_ = servertype;
    cout << "Retrieved host " << server_->h_name << ".." <<endl;

    cout << "Setting up server address.." << endl;
        /*Set up server address*/
    bzero((char*) &server_address_, sizeof(server_address_));
    server_address_.sin_family = AF_INET;

    cout << "Copying address to server->h_addr.." << endl;
    bcopy((char*)server_->h_addr,
         (char*)&server_address_.sin_addr.s_addr,
         server_->h_length);

    cout << "Assigning server port.." << endl;
    server_address_.sin_port = htons(portno);
}


void Clientsocket::connect_()
{
    /*Connect to server*/
    if (UDP_) return;
    cout << "Connecting to server.." << endl;
    if (connect(sockfd_,(const sockaddr*)&server_address_,sizeof(server_address_))<0)
    {
        error("ERROR connecting to server");
    }

    /*Print debug-info*/
    cout << "Server information:" << endl;
    cout << "IP4: " << server_address_.sin_addr.s_addr <<endl;
    cout << "Port: " << server_address_.sin_port <<endl;
}

int Clientsocket::getSocketFd()
{
    return sockfd_;
}

int Clientsocket::open_()
{
    /*Open socket depending on protocol*/
    cout << "Opening socket.." << endl;
    if (sockettype_ == UDP_)
    {
        sockfd_ = socket(AF_INET,SOCK_DGRAM,0);
        if (sockfd_<0)
        {
            error("ERROR opening socket on UDP!");
        }
    } else {
        sockfd_ = socket(AF_INET,SOCK_STREAM,0);
        if (sockfd_<0)
        {
            error("ERROR opening socket on TCP!");
        }
    }
}

void Clientsocket::sendMessage(char* str)
{
    if (sockettype_ == UDP_)
    {
        /*UDP Sending syntax*/
        int n = sendto(getSocketFd(),str,strlen(str),
                       0,
                       (const struct sockaddr*)&server_address_,
                       sizeof(struct sockaddr_in));
        if (n < 0)
        {
            error("ERROR Writing to socket with UDP!");
        }
    } else {
        /*TCP Sending syntax*/
        int n = write(getSocketFd(),str,strlen(str));
        if (n < 0)
        {
            error("ERROR Writing to socket with TCP!");
        }
    }
}

char* Clientsocket::listen_(int* byte_count, int no_b_read)
{
    if (sockettype_ == UDP_)
    {
        unsigned int length = sizeof(struct sockaddr_in);
        int n = recvfrom(getSocketFd(), buffer_, no_b_read,
                         0,
                         (struct sockaddr*)&server_address_,
                         &length);
        *byte_count += n;
        if(0>n){
            error("ERROR reading from socket with UDP");
            return "";
        } else {
            return buffer_;
        }
    } else {
        int n = recv(getSocketFd(), buffer_, no_b_read,0);
        *byte_count += n;

        if(0>n){
            error("ERROR reading from socket with TCP");
            return "";
        } else {
            return buffer_;
        }
    }
}
