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

    fileHandler FileH;
    FileH.printFiles();
    string file = "Picture1.jpg";
    if (FileH.checkForFile(file))
    {
        //cout << FileH.openFile(file) << endl;
        cout << FileH.getSize(file) << endl;
    } else
    {
        cout << file << " doesnt exist!" << endl;
    }

    /*Make message*/
    message myMessage(FileH, file, 1000);
    myMessage.printMessage(0);
    cout << myMessage.getNumberOfMessages() << " : " << (double)FileH.getSize(file)/1000.0 << endl;
    file_message fm;
    fm = myMessage.parseFileMessage(myMessage.getMessages());
    cout << "Size of file: " << fm.fileSize << endl;
    cout << "Size of datastring: " << fm.data.size() << endl;

//    /*Make socket object*/
//    bsocket Server("10.0.0.1",9000);

//    /*Open socket*/
//    Server._open();
//    Server._listen();

    return 0;
}

