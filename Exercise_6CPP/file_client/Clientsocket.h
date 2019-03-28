#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H
#include <string>
#include <netinet/in.h>

class Clientsocket
{
public:
    Clientsocket(char* target_ip, int portno);
    void connect_();
    int open_();
    char *listen_(int* bytecount,int no_b_read);
    void sendMessage(char* str);

protected:
    int getSocketFd();

private:
    struct hostent *server_;
    struct sockaddr_in server_address_;
    struct sockaddr_in client_address_;
    int sockfd_, newsockfd_, portno_, clilen_, pid_;
    char buffer_[2048];
};

#endif // CLIENT_SOCKET_H