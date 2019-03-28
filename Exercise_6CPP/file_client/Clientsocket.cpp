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

Clientsocket::Clientsocket(char* target_ip, int portno)
{
    /*Defintions*/
    cout << "Initializing variables.." << endl;
    server_ = gethostbyname(target_ip);
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
    /*Open socket */
    cout << "Opening socket.." << endl;
    sockfd_ = socket(AF_INET,SOCK_STREAM,0);
    if (sockfd_<0)
    {
        error("ERROR opening socket!");
    }
}

void Clientsocket::sendMessage(char* str)
{
    int n = write(getSocketFd(),str,strlen(str));
    if (n < 0)
    {
        error("ERROR Writing to socket!");
    }
}

char* Clientsocket::listen_(int* byte_count, int no_b_read)
{
    int n = recv(getSocketFd(), buffer_, no_b_read,0);
    *byte_count += n;

    if(0>n){
        error("ERROR reading from socket");
        return "";
    } else {
        return buffer_;
    }
}
