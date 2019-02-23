#ifndef SERVER_H
#define SERVER_H


class server
{
public:
    server(char* ip, int portno);
    void sendFile(string fileName, long fileSize, int outToClient);
    void recieve();
    void error(char* str);

private:
    char _buffer[256];
    struct sockaddr_in _server_address;
    struct sockaddr_in _client_address;
    int _sockfd, _newsockfd, _portno, _clilen, _pid;
    bool keepOpen = true;

    /*Structure for sending packages*/
    struct _package {
       string fileName;
       long fileSize;
    };
};

#endif // SERVER_H
