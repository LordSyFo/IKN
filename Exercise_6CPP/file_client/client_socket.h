#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H
#include </root/Git/IKN/Exercise_6CPP/file_server/bsocket.h>

class client_socket:public bsocket
{
public:
    client_socket(char* target_ip, int portno);
    void _connect();

private:
    struct hostent *_server;
};

#endif // CLIENT_SOCKET_H
