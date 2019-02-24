#include "client_socket.h"
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

client_socket::client_socket(char* target_ip, int portno)
{


    /*Defintions*/
    cout << "Initializing variables.." << endl;
    _server = gethostbyname(target_ip);
    cout << "Retrieved host " << _server->h_name << ".." <<endl;

    cout << "Setting up server address.." << endl;
        /*Set up server address*/
    bzero((char*) &_server_address, sizeof(_server_address));
    _server_address.sin_family = AF_INET;

    cout << "Copying address to server->h_addr.." << endl;
    bcopy((char*)_server->h_addr,
         (char*)&_server_address.sin_addr.s_addr,
         _server->h_length);

    cout << "Assigning server port.." << endl;
    _server_address.sin_port = htons(portno);
}

void client_socket::_connect()
{
    /*Connect to server*/
    cout << "Connecting to server.." << endl;
    if (connect(_sockfd,(const sockaddr*)&_server_address,sizeof(_server_address))<0)
    {
        error("ERROR connecting to server");
    }

    /*Print debug-info*/
    cout << "Server information:" << endl;
    cout << "IP4: " << _server_address.sin_addr.s_addr <<endl;
    cout << "Port: " << _server_address.sin_port <<endl;
}

int client_socket::_getSockFd()
{
    return _sockfd;
}

int client_socket::_open()
{
    /*Open socket */
    cout << "Opening socket.." << endl;
    _sockfd = socket(AF_INET,SOCK_STREAM,0);
    if (_sockfd<0)
    {
        error("ERROR opening socket!");
    }
}


void client_socket::listen_callback()
{
    _recieve();
    cout << "Recieved: " << _buffer;
}
