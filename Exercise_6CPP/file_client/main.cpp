//============================================================================
// Name        : file_client.cpp
// Author      : Lars Mortensen
// Version     : 1.0
// Description : file_client in C++, Ansi-style
//============================================================================
#include "client_socket.h"
#include <iostream>
#include "/root/Git/IKN/Exercise_6CPP/file_server/message.h"
#include <string>

using namespace std;

//const char* server_INET = "10.0.0.1";
//const char* client_INET = "10.0.0.2";


int main(int argc, char *argv[])
{    
    if (argc < 2)
    {
        cout << "Usage: \.exe \"Filename with extension\"" << endl;
        return 0;
    }
    std::string filename_str = argv[1];

    client_socket Client("10.0.0.1",9000);
    Client.open_();
    Client.connect_();

    /*Make message object for recieved message*/
    message myMessage;

    /*Send file-request message to server*/
    cout << "Requesting " << filename_str << " from server.." << endl;
    Client.sendMessage((char*)filename_str.c_str());
    Client.listen_();

    return 0;

}
