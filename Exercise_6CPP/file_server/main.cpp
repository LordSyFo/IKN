//============================================================================
// Name        : file_server.cpp
// Author      : Lars Mortensen
// Version     : 1.0
// Description : file_server in C++, Ansi-style
//============================================================================

#include "bsocket.h"
#include "filehandler.h"
#include <iostream>
#include "message.h"
#include <unistd.h>
#include <string.h>
#include <fstream>

using namespace std;

//void sendFile(string fileName, long fileSize, int outToClient);
//void recieve(int sock);

//const char* server_INET = "10.0.0.1";
//const char* client_INET = "10.0.0.2";


void error(char* str)
{
    perror(str);
    exit(1);
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
    /*Make filehandler and find available files*/
    fileHandler FileH;
    cout << "Available files: " << endl;
    FileH.printFiles();

    /*Define chunksize here:*/
    int chunk_size = 1000;

    /*Make socket object*/
    bsocket Server("10.0.0.1",9000);

    /*Open socket*/
    Server._open();
    string request_buffer;
    while(1)
    {
        /*Wait for request from client*/
        cout << "Listening for clients.." << endl;
        request_buffer = Server._listen();
        if (request_buffer != "")
        {
            cout << "Checking for requested file: " << request_buffer << ".." << endl;
            if (FileH.checkForFile(request_buffer))
            {
                cout << FileH.getSize(request_buffer) << endl;

                /*Make message*/
                message myMessage(FileH, request_buffer, chunk_size);
                myMessage.printMessage(0);  //Message[0] = header

                /*Make file_message struct for debugging purposes*/
                file_message fm;
                fm = myMessage.parseFileMessage(myMessage.getMessages());
                cout << "Size of file: " << fm.fileSize << endl;
                cout << "Extension of file: " << fm.fileType << endl;

                /*Begin to transmit messages*/
                FileH.sendFile(myMessage.getHeader(),Server,request_buffer,1000,10000);

                cout << "Finished transmitting data!" << endl;

            } else
            {
                cout << request_buffer << " doesnt exist!" << endl;
                message errorMessage;
                errorMessage.printMessage(0);
                string tmp = errorMessage.getHeader();
                Server.sendMessage((char*)tmp.c_str(),strlen(tmp.c_str()));
            }
        }
        cout << "Getting ready for new connections.." << endl;
    }
    return 0;
}

