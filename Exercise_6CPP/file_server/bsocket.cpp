#include "bsocket.h"
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

bsocket::bsocket()
{

}

bsocket::bsocket(char* ip, int portno)
{
    cout << "Initializing variables.." << endl;
    /*Declarations and assignments*/
    bzero((char*) &_server_address, sizeof(_server_address)); //Fill address with zeros
    _portno = portno;

    cout << "Initializing server structures.." << endl;
    /*Fill server address struct*/
    _server_address.sin_family       = AF_INET;
    _server_address.sin_port         = htons(_portno);

    if (!inet_pton(AF_INET, ip, &_server_address.sin_addr))  //Host IP ETH1
    {
        error("ERROR Converting text-address to binary");
    };
}

int bsocket::_open()
{
    cout << "Creating/Opening socket on " << _server_address.sin_addr.s_addr << ":" << _server_address.sin_port <<endl;
    /*Create socket*/
    _sockfd = socket(AF_INET,SOCK_STREAM,0);
    if (_sockfd<0)
    {
        error("ERROR Opening socket!");
        return 0;
    }

    cout << "Binding socket to address.." << endl;
    /*Bind socket to address*/
    if (bind(_sockfd, (struct sockaddr*) &_server_address, sizeof(_server_address)) < 0)
    {
        error("ERROR Binding socket to address!");
        return 0;
    }

    return 1;
}

void bsocket::_listen()
{

    cout << "Listening for message.." << endl;
    /*Listen for server*/
    listen(_sockfd,5);   //Maybe change 1 to 5

    /*Wait for client-connection*/
    while(keepOpen)
    {
        _clilen      = sizeof(_client_address);
        _newsockfd   = accept(_sockfd,(struct sockaddr*) &_client_address, (socklen_t*)&_clilen);
        if (_newsockfd < 0 )
        {
            error("ERROR on accept!");
        }
        _pid = fork();
        if(_pid < 0)
        {
            error("ERROR on fork!");
        }
        if (_pid == 0)
        {
            close(_sockfd);
            listen_callback();
            exit(0);
        }
    }
}

void bsocket::listen_callback()
{
    _recieve();
    cout << "Recieved: " << _buffer;
    _awkToClient();
}

char* bsocket::_recieve()
{
    int n;
    /*Read from socket*/
    bzero(_buffer,256);
    n = read(getSocketFd(),_buffer,255);
    if (n < 0) error("ERROR reading from socket");
    return _buffer;
}

void bsocket::_awkToClient()
{
    /*AWK to client*/
    int n;
    cout << "Attempting to AWK back to client!" << endl;
    strcpy(_buffer,"I got your message!");
    n = write(getSocketFd(),_buffer,strlen(_buffer));
    if (n < 0)
    {
        error("ERROR Writing AWK back to client!");
    }
}

int bsocket::getSocketFd()
{
    return _newsockfd;
}

void bsocket::_sendMessage(char* str)
{
    int n = write(getSocketFd(),str,strlen(str));
    if (n < 0)
    {
        error("ERROR Writing to socket!");
    }
}

/**
 * Sender filen som har navnet fileName til klienten
 *
 * @param fileName Filnavn som skal sendes til klienten
 * @param fileSize Størrelsen på filen, 0 hvis den ikke findes
 * @param outToClient Stream som der skrives til socket
     */
void bsocket::sendFile(string fileName, long fileSize, int outToClient)
{
    // TO DO Your own code
}


void bsocket::error(char* str)
{
    perror(str);
    exit(1);
}
