#ifndef SERVER_H
#define SERVER_H
#include <string>
#include <netinet/in.h>

class bsocket
{
public:
    bsocket();
    bsocket(char* ip, int portno);
    void sendFile(std::string fileName, long fileSize, int outToClient);
    virtual char* _recieve();
    void error(char* str);
    virtual void _listen();
    virtual int _open();
    void _awkToClient();
    virtual void _sendMessage(char* str);

protected:
    char _buffer[256];
    struct sockaddr_in _server_address;
    struct sockaddr_in _client_address;
    int _sockfd, _newsockfd, _portno, _clilen, _pid;
    bool keepOpen = true;

    /*Structure for sending packages*/
    struct _package {
       std::string fileName;
       long fileSize;
    };

    /*Private methods*/
    virtual void listen_callback();
    virtual int getSocketFd();
};

#endif // SERVER_H
