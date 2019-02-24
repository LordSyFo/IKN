//============================================================================
// Name        : file_client.cpp
// Author      : Lars Mortensen
// Version     : 1.0
// Description : file_client in C++, Ansi-style
//============================================================================
#include "client_socket.h"
#include <iostream>

using namespace std;

//void receiveFile(string fileName, int socketfd);

//const char* server_INET = "10.0.0.1";
//const char* client_INET = "10.0.0.2";


int main(int argc, char *argv[])
{    

    client_socket Client("10.0.0.1",9000);
    Client._open();
    Client._connect();


    /*Send test message*/
    cout << "Attempting to send message to server.." << endl;
    Client._sendMessage("Hello world!");
    Client._listen();

    return 0;

}

/**
 * Modtager filstørrelsen og udskriver meddelelsen: "Filen findes ikke" hvis størrelsen = 0
 * ellers
 * Åbnes filen for at skrive de bytes som senere modtages fra serveren (HUSK kun selve filnavn)
 * Modtag og gem filen i blokke af 1000 bytes indtil alle bytes er modtaget.
 * Luk filen, samt input output streams
 *
 * @param fileName Det fulde filnavn incl. evt. stinavn
 * @param sockfd Stream for at skrive til/læse fra serveren
 */
void receiveFile(string fileName, int sockfd)
{
	// TO DO Your own code
}

