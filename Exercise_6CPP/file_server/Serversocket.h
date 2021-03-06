#ifndef SERVER_H
#define SERVER_H
#include <string>
#include <netinet/in.h>

enum{TCP,UDP};

class Serversocket
{
public:
    Serversocket();
    Serversocket(char* ip, int portno,int socktype = TCP);
    void sendFile(std::string fileName, long fileSize, int outToClient);
    void error(const char* str);
    virtual std::string _listen();
    virtual int _open();
    void sendMessage(char* str,int no_bytes);
    void closeConnections();

protected:
    char buffer_[256];
    struct sockaddr_in server_address_;
    struct sockaddr_in client_address_;
    int sockfd_, newsockfd_, portno_, clilen_, pid_;
    bool keepOpen = true;
    int sockettype_ = TCP;

    /*Structure for sending packages*/
    struct _package {
       std::string fileName;
       long fileSize;
    };

    /*Private methods*/
    virtual int getSocketFd();
};

#endif // SERVER_H
