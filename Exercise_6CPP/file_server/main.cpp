//============================================================================
// Name        : file_server.cpp
// Author      : Lars Mortensen
// Version     : 1.0
// Description : file_server in C++, Ansi-style
//============================================================================

#include "Serversocket.h"
#include "Filehandler.h"
#include <iostream>
#include "Message.h"
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
    Filehandler FileH;
    cout << "Available files: " << endl;
    FileH.printFiles();

    /*Define chunksize here:*/
    int chunk_size = 1000;

    /*Make socket object*/
    Serversocket Server("10.0.0.1",9000,UDP);

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
                Message myMessage(FileH, request_buffer, chunk_size);
                myMessage.printMessage(0);  //Message[0] = header

                /*Make file_message struct for debugging purposes*/
                file_message fm;
                fm = myMessage.parseFileMessage(myMessage.getMessages());
                cout << "Size of file: " << fm.fileSize << endl;
                cout << "Extension of file: " << fm.fileType << endl;
                cout << "Chunksize of file: " << fm.chunkSize << endl;

                /*Begin to transmit messages*/
                FileH.sendFile(myMessage.getHeader(),Server,request_buffer,1000,10000);

                cout << "Finished transmitting data!" << endl;

            } else if (request_buffer!="U"&&request_buffer!="u"&&request_buffer!="L"&&request_buffer!="l")
            {
                cout << request_buffer << " doesnt exist!" << endl;
                Message errorMessage;
                errorMessage.printMessage(0);
                string tmp = errorMessage.getHeader();
                Server.sendMessage((char*)tmp.c_str(),strlen(tmp.c_str()));
            } else if (request_buffer=="U"||request_buffer=="u") {
                cout << "Client requested for uptime!" << endl;
                cout << "Catching uptime!" << endl;
                ifstream fin("/proc/uptime");
                string strbuffer;
                if (getline(fin,strbuffer))
                {
                    cout << "Sending: "<< strbuffer << endl;
                    Server.sendMessage((char*)strbuffer.c_str(),strlen(strbuffer.c_str()));
                }

            } else if(request_buffer=="L"||request_buffer=="l")
            {
                cout << "Client requested for average load!" << endl;
                cout << "Catching average load!" << endl;
                ifstream fin("/proc/loadavg");
                string strbuffer;
                if (getline(fin,strbuffer))
                {
                    cout << "Sending: "<< strbuffer << endl;
                    Server.sendMessage((char*)strbuffer.c_str(),strlen(strbuffer.c_str()));
                }
            }
        }
        cout << "Getting ready for new connections.." << endl;
    }
    return 0;
}

