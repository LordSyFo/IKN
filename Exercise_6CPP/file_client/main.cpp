//============================================================================
// Name        : file_client.cpp
// Author      : Lars Mortensen
// Version     : 1.0
// Description : file_client in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iknlib.h>

using namespace std;

void receiveFile(string fileName, int socketfd);

const char* server_INET = "10.0.0.1";
const char* client_INET = "10.0.0.2";

void error(char* str)
{
    perror(str);
    exit(1);
}


int main(int argc, char *argv[])
{    
    /*Defintions*/
    cout << "Initializing variables.." << endl;
    int sockfd, portno, n;
    struct sockaddr_in server_address;
    struct hostent *server;
    portno = 9000;

    /*Open socket */
    cout << "Opening socket.." << endl;
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if (sockfd<0)
    {
        error("ERROR opening socket!");
    }

    server = gethostbyname("10.0.0.1");

    cout << "Retrieved host " << server->h_name << ".." <<endl;

    cout << "Setting up server address.." << endl;
    /*Set up server address*/
    bzero((char*) &server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;

    cout << "Copying address to server->h_addr.." << endl;
    bcopy((char*)server->h_addr,
          (char*)&server_address.sin_addr.s_addr,
          server->h_length);

    cout << "Assigning server port.." << endl;
    server_address.sin_port = htons(portno);

    /*Connect to server*/
    cout << "Connecting to server.." << endl;
    if (connect(sockfd,(const sockaddr*)&server_address,sizeof(server_address))<0)
    {
        error("ERROR connecting to server");
    }

    cout << "Server information:" << endl;
    cout << "IP4: " << server_address.sin_addr.s_addr <<endl;
    cout << "Port: " << server_address.sin_port <<endl;

    /*Send test message*/
    cout << "Attempting to send message to server.." << endl;
    char* buffer = "Hello world!";
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0)
    {
        error("ERROR Writing to socket!");
    }

    /*Recieve response*/
    cout << "Recieving response from server.." << endl;
    bzero(buffer,sizeof(buffer));
    n = read(sockfd,buffer,sizeof(buffer)-1);
    if (n < 0)
    {
        error("ERROR Reading from socket");
    }
    printf("Recieved: %s", buffer);
    return 0;

}

/**
 * Modtager filstørrelsen og udskriver meddelelsen: "Filen findes ikke" hvis størrelsen = 0
 * ellers
 * Åbnes filen for at skrive de bytes som senere modtages fra serveren (HUSK kun selve filnavn)
 * Modtag og gem filen i blokke af 1000 bytes indtil alle bytes er modtaget.
 * Luk filen, samt input output streams
 *
 * @param fileName Det fulde filnavn incl. evt. stinavn
 * @param sockfd Stream for at skrive til/læse fra serveren
 */
void receiveFile(string fileName, int sockfd)
{
	// TO DO Your own code
}

