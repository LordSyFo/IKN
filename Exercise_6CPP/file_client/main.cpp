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
#include <cmath>
#include <string.h>
#include <stdlib.h>

using namespace std;

//const char* server_INET = "10.0.0.1";
//const char* client_INET = "10.0.0.2";


int main(int argc, char *argv[])
{    
    if (argc < 2)
    {
        cout << "Usage: \\.exe \"Filename with extension\"" << endl;
        return 0;
    }
    std::string filename_str = argv[1];

    client_socket Client("10.0.0.1",9000);
    Client.open_();
    Client.connect_();

    /*Make message object for recieved message*/
    message myMessage;
    vector<char*>(messages);

    /*Send file-request message to server*/
    cout << "Requesting " << filename_str << " from server.." << endl;
    Client.sendMessage((char*)filename_str.c_str());

    /*Listen for header*/
    int recieved = 0;
    int sendLength = 1000;  //TODO: Should be passed in header
    char* header = Client.listen_(&recieved,sendLength);
    messages.push_back(header);

    /*If header isn't empty listen to rest of messages*/
    if (header != "")
    {
        /*Parse message to get fields including file-size*/
        cout << "Recieved header.." << endl;
        file_message fm;
        fm = myMessage.parseFileMessage(messages);

        cout << "Header string length: " << strlen(header) <<endl;
        cout << "Filesize: " << fm.fileSize << endl;
        size_t iterations = ceil(fm.fileSize/sendLength);
        recieved    = 0;   //Reset bytes recieved var
        int i       = 0;

        while(recieved < fm.fileSize)
        {
            /*Dont read 1000 characters if it exceeds filesize*/
            if (recieved+sendLength>fm.fileSize)
            {
                messages.push_back(Client.listen_(&recieved,sendLength-(recieved+sendLength-fm.fileSize)));
            } else
            {
                messages.push_back(Client.listen_(&recieved,1000));
            }
            cout << i << endl;
            //system("CLS");
            cout << "Messages recieved: " << messages.size() << endl;
            cout << "Recieved: " << recieved << " / " << fm.fileSize << endl;
            i++;
        }

        cout << "Finished recieving file!" << endl;
        fm = myMessage.parseFileMessage(&messages);

        cout << "-----FILE INFORMATION-----" << endl;
        cout << "Size: " << fm.fileSize << endl;
        cout << "Type: " << fm.fileType << endl;
        //cout << "Recieved bytes: " << fm.data.length() << endl;
    }

    return 0;

}
