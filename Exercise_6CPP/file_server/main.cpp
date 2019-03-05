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
    //cout << "Datastring: " << fm.data << endl;

    //FileH.makeFileFromBinary(fm,"test");

    fileHandler FileH;
    cout << "Available files: " << endl;
    FileH.printFiles();

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
                message myMessage(FileH, request_buffer, 1000);
                myMessage.printMessage(0);
                cout << myMessage.getNumberOfMessages() << " : " << (double)FileH.getSize(request_buffer)/1000.0 << endl;
                file_message fm;
                fm = myMessage.parseFileMessage(myMessage.getMessages());
                cout << "Size of file: " << fm.fileSize << endl;
                cout << "Extension of file: " << fm.fileType << endl;

                /*Begin to transmit messages*/
                FileH.sendFile(myMessage.getHeader(),Server,request_buffer,1000);

                cout << "Finished transmitting data!" << endl;

            } else
            {
                cout << request_buffer << " doesnt exist!" << endl;
            }
        }
        cout << "Getting ready for new connections.." << endl;
    }
    return 0;
}

