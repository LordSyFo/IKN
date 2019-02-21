//============================================================================
// Name        : file_server.cpp
// Author      : Lars Mortensen
// Version     : 1.0
// Description : file_server in C++, Ansi-style
//============================================================================

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

using namespace std;

void sendFile(string fileName, long fileSize, int outToClient);

const char* server_INET = "10.0.0.1";
const char* client_INET = "10.0.0.2";

void error(char* str)
{
    perror(str);
    exit(1);
}

struct package {
   string fileName;
   long fileSize;
}

/**
 * main starter serveren og venter på en forbindelse fra en klient
 * Læser filnavn som kommer fra klienten.
 * Undersøger om filens findes på serveren.
 * Sender filstørrelsen tilbage til klienten (0 = Filens findes ikke)
 * Hvis filen findes sendes den nu til klienten
 *
 * HUSK at lukke forbindelsen til klienten og filen nÃ¥r denne er sendt til klienten
 *
 * @throws IOException
 *
 */
int main(int argc, char *argv[])
{
    /*Defintions*/
    int sockfd, newsockfd, portno, clilen, n;
    struct sockaddr_in server_address, client_address;

    /*Declarations and assignments*/
    bzero((char*) &server_address, sizeof(server_address)); //Fill address with zeros
    portno = 9000;

    /*Fill server address struct*/
    server_address.sin_family = AF_INET;
    server_address.sin_port   = htons(portno);
    server_address.sin_addr   = server_INET;   //Host IP ETH1 - (INADDR_ANY: gets local ip)

    /*Create socket*/
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if (sockfd<0)
    {
        error("ERROR Opening socket!");
    }

    /*Bind socket to address*/
    if (bind(sockfd, (struct sockaddr*) &server_address, sizeof(server_address)) < 0)
    {
        error("ERROR Binding socket to address!");
    }

    /*Listen for server*/
    listen(sockfd,5);   //Maybe change 1 to 5

    /*Wait for client-connection*/
    while(1)
    {
        clilen      = sizeof(client_address);
        newsockfd   = accept(sockfd,(struct sockaddr*) &client_address, &clilen);
        if (newsockfd < 0 )
        {
            error("ERROR on accept!");
        }
        pid = fork();
        if(pid < 0)
        {
            error("ERROR on fork!");
        }
        if (pid == 0)
        {
            close(sockfd);
            exit(0);
        }

    }
    return 0;
}

void recieve(int sock)
{
    int n;
    char buffer[256];

    /*Read from socket*/
    bzero(buffer,256);
    n = read(sock,buffer,255);
    if (n < 0) error("ERROR reading from socket");
    printf("Here is the message: %s\n",buffer);
    n = write(sock,"I got your message",18);
    if (n < 0) error("ERROR writing to socket");

    /*AWK to client*/
    n = write(newsockfd,buffer,sizeof(buffer)-1);
    if (n < 0)
    {
        error("ERROR Writing AWK back to client!");
    }
}

/**
 * Sender filen som har navnet fileName til klienten
 *
 * @param fileName Filnavn som skal sendes til klienten
 * @param fileSize Størrelsen på filen, 0 hvis den ikke findes
 * @param outToClient Stream som der skrives til socket
     */
void sendFile(string fileName, long fileSize, int outToClient)
{
    // TO DO Your own code
}

