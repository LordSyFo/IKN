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
    string str_buffer;
    while(1)
    {
        /*Wait for request from client*/
        str_buffer = Server._listen();
        if (str_buffer != "")
        {
            cout << "Checking for requested file: " << str_buffer << ".." << endl;
            if (FileH.checkForFile(str_buffer))
            {
                //cout << FileH.openFile(file) << endl;
                cout << FileH.getSize(str_buffer) << endl;

                /*Make message*/
                message myMessage(FileH, str_buffer, 1000);
                myMessage.printMessage(0);
                cout << myMessage.getNumberOfMessages() << " : " << (double)FileH.getSize(str_buffer)/1000.0 << endl;
                file_message fm;
                fm = myMessage.parseFileMessage(myMessage.getMessages());
                cout << "Size of file: " << fm.fileSize << endl;
                cout << "Extension of file: " << fm.fileType << endl;

                /*Begin to transmit messages*/
                vector<char*>(messages) = myMessage.getMessages();
                int count = 0;
                /*
                cout << "Sending " << messages.size() << " messages!" << endl;
                for(vector<char*>::iterator i = messages.begin(); i != messages.end(); ++i) {
                    cout << count++ << endl;
                    //cout << "Message size: " << strlen(i) << endl;
                    Server.sendMessage(*i,1000);
                    usleep(500);   //Sleep for debug
                }
                */
                cout << "Finished transmitting data!" << endl;

                char* buffer = new char[fm.fileSize];
                for(vector<char*>::iterator i = messages.begin()+1; i != messages.end(); ++i) {
                    strcat(buffer,*i);
                }

                //FÅR EN MÆRKELIG KOPI UD?? HMMM
                fm.data = buffer;
                cout << fm.data << endl;
                FileH.makeFileFromBinary(fm,"testcpy");

            } else
            {
                cout << str_buffer << " doesnt exist!" << endl;
            }
        }
    }
    return 0;
}

