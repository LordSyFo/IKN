#include "Serversocket.h"
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

using namespace std;

Serversocket::Serversocket()
{

}

Serversocket::Serversocket(char* ip, int portno, int socktype)
{
    cout << "Initializing variables.." << endl;
    /*Declarations and assignments*/
    bzero((char*) &server_address_, sizeof(server_address_)); //Fill address with zeros
    portno_ = portno;
    sockettype_ = socktype;

    cout << "Initializing server structures.." << endl;
    /*Fill server address struct*/
    server_address_.sin_family       = AF_INET;
    server_address_.sin_port         = htons(portno_);

    if (!inet_pton(AF_INET, ip, &server_address_.sin_addr))  //Host IP ETH1
    {
        error("ERROR Converting text-address to binary");
    };
}

int Serversocket::_open()
{
    cout << "Creating/Opening socket on " << server_address_.sin_addr.s_addr << ":" << server_address_.sin_port <<endl;
    /*Create socket based on sockettype member variable*/
    /*( SOCK_STREAM for TCP / SOCK_DGRAM for UDP ) set type=0 to use sockettype as protocol*/
    if (sockettype_ == TCP) sockfd_ = socket(AF_INET,SOCK_STREAM,0);
    else sockfd_ = socket(AF_INET,SOCK_DGRAM,0);

    if (sockfd_<0)
    {
        error("ERROR Opening socket!");
        return 0;
    }

    cout << "Binding socket to address.." << endl;
    /*Bind socket to address*/
    if (bind(sockfd_, (struct sockaddr*) &server_address_, sizeof(server_address_)) < 0)
    {
        error("ERROR Binding socket to address!");
        return 0;
    }

    return 1;
}

std::string Serversocket::_listen()
{
    //cout << "Listening for message.." << endl;
    /*Listen for server*/
    if (sockettype_ == UDP)
    {
        clilen_         = sizeof(client_address_);
        int n           = 0;
        bzero(buffer_,256);
        n = recvfrom(sockfd_,buffer_,255,0,(struct sockaddr*) &client_address_,(socklen_t*)&clilen_);
        if (n<0)
        {
            error("ERROR Recieving from socket with UDP");
        }
        newsockfd_ = sockfd_;
        return buffer_;
    } else {

    listen(sockfd_,5);   //Maybe change 1 to 5

    /*Wait for client-connection*/
    clilen_      = sizeof(client_address_);
    newsockfd_   = accept(sockfd_,(struct sockaddr*) &client_address_, (socklen_t*)&clilen_);

    if (newsockfd_ < 0 )
    {
        error("ERROR on accept!");
    }

    /*Read from socket*/
    bzero(buffer_,256);
    int n = read(getSocketFd(),buffer_,255);
    if (n < 0) {
        error("ERROR reading from socket");
    }

    return buffer_;
    }
}

int Serversocket::getSocketFd()
{
    return newsockfd_;
}

void Serversocket::sendMessage(char* str,int no_bytes)
{
    //cout<<"Message length in sendMessage(): "<<strlen(str)<<endl;
    if (sockettype_ == UDP)
    {
        int n = sendto(getSocketFd(),str,no_bytes,0,(struct sockaddr*) &client_address_,clilen_);
        if (n<0)
        {
            error("ERROR Sending to socket with UDP");
        }
    } else {
    int n = write(getSocketFd(),str,no_bytes);
    if (n < 0)
    {
        error("ERROR Writing to socket!");
    }
    if (n < no_bytes)
    {
        cout << "Couldn't send everything to client" << endl;
        cout << "Only sent " << n << " bytes.." << endl;
    }
    cout<<"Succesfully send message"<<endl;
    }
}

void Serversocket::error(const char* str)
{
    perror(str);
    exit(1);
}

void Serversocket::closeConnections()
{
    /*Close sockets*/
    close(newsockfd_);close(sockfd_);
}
