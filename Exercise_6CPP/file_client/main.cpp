//============================================================================
// Name        : file_client.cpp
// Author      : Lars Mortensen
// Version     : 1.0
// Description : file_client in C++, Ansi-style
//============================================================================
#include "Clientsocket.h"
#include <iostream>
#include "/root/Git/IKN/Exercise_6CPP/file_server/Message.h"
#include <string>
#include <cmath>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <unistd.h>

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

    Clientsocket Client("10.0.0.1",9000,TCP_);

    Client.open_();
    Client.connect_();

    /*Make message object for recieved message*/
    Message myMessage;
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
    if (strcmp(header,"")!=0)
    {
        /*Parse message to get fields including file-size*/
        //cout << "Recieved header.." << endl;
        file_message fm;
        fm = myMessage.parseFileMessage(messages);

        if (strlen(header)<100|| fm.fileName == "N/A" && fm.fileType == "N/A")
        {
            cout << "Server could not find requested file!"<<endl;
            cout<<"Please try requesting a different file.."<<endl;
            cout<<"Message from server: " << endl;
            cout<<header<<endl;
            return 0;
        }

        /*Print parsed header information*/
        cout << "----HEADER INFORMATION----" << endl;
        cout << "Header string length: " << strlen(header) <<endl;
        cout << "Filesize: " << fm.fileSize << endl;
        cout << "Chunksize: " << fm.chunkSize << endl;
        cout << "Filename: " << fm.fileName << endl;
        cout << "Filetype: " << fm.fileType << endl;

        /*Variables for keeping track of recieved bytes*/
        recieved    = 0;   //Reset bytes recieved var

        /*Make filestream*/
        ofstream fout(fm.fileName, ios::binary);
        unsigned char *buffer = new unsigned char[fm.chunkSize]; //DYNAMIC!
        int prev_recieved = 0;

        while(recieved < fm.fileSize)
        {
            prev_recieved=recieved;
            memcpy(buffer,(char*)Client.listen_(&recieved,fm.chunkSize),fm.chunkSize);
            fout.write((char*)buffer,recieved-prev_recieved);
            cout << "Messages recieved: " << messages.size() << endl;
            cout << "Recieved: " << recieved << " / " << fm.fileSize << endl;
        }

        cout << "Finished recieving file!" << endl;
        cout << "-----FILE INFORMATION-----" << endl;
        cout << "Size: " << fm.fileSize << endl;
        cout << "Type: " << fm.fileType << endl;
        cout << "Filename: " << fm.fileName << endl;
        cout << "File downloaded " << fm.chunkSize << " bytes at a time." << endl;
        fout.close();
    }

    return 0;

}
