#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H
#include <string>
#include <netinet/in.h>

class client_socket
{
public:
    client_socket(char* target_ip, int portno);
    void connect_();
    int open_();
    std::string listen_();
    void sendMessage(char* str);

protected:
    int getSocketFd();

private:
    struct hostent *server_;
    struct sockaddr_in server_address_;
    struct sockaddr_in client_address_;
    int sockfd_, newsockfd_, portno_, clilen_, pid_;
    char buffer_[256];
};

#endif // CLIENT_SOCKET_H
