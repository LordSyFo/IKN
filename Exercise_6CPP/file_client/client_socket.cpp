#include "client_socket.h"
#include "stdlib.h"

client_socket::client_socket(char* target_ip, int portno): _portno(portno)
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

client_socket::_connect()
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

bsocket::_open()
{
    /*Open socket */
    cout << "Opening socket.." << endl;
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if (sockfd<0)
    {
        error("ERROR opening socket!");
    }
}


bsocket::listen_callback(int sock)
{
    return 0;
}
