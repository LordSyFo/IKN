#include "filehandler.h"
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include "bsocket.h"
#include <unistd.h>

using namespace std;

fileHandler::fileHandler()
{
    updateFilesInCurrentFolder();
}


void fileHandler::printFiles()
{
    for (vector<string>::iterator it = files.begin(); it != files.end(); ++it)
        cout << *it << endl;
}

char* fileHandler::openFile(string fileName)
{
    char* buffer; long filesize;

    /*Open file in stream*/
    ifstream fin(fileName.insert(0,fileDir),ios::in|ios::binary|ios::ate);

    /*Get size of file and reset to begin*/
    filesize = fin.tellg();
    fin.seekg(0,ios::beg);

    /*Allocate filesize in char array buffer*/
    buffer = new char[filesize];

    /*Read file binary into buffer*/
    fin.read(buffer,filesize);
    fin.close();

    /*Save filesize in attribute*/
    filesize_ = filesize;

    return buffer;
}

int fileHandler::updateFilesInCurrentFolder()
{
    DIR* dirp = opendir(fileDir.c_str());
    struct dirent * dp;
    while((dp=readdir(dirp)) != NULL)
    {
        files.push_back(dp->d_name);
    }
    closedir(dirp);
}

bool fileHandler::checkForFile(const std::string str){
    if (std::find(files.begin(), files.end(), str) != files.end())
    {
        return true;
    }
    return false;
}

int fileHandler::getSize(std::string str)
{
    if (checkForFile(str))
    {
        /*Open file in stream*/
        ifstream fin(str.insert(0,fileDir),ios::in|ios::binary|ios::ate);
        /*Get size of file*/
        long size = fin.tellg();
        fin.close();
        return size;
    }
    return -1;
}

int fileHandler::sendFile(string header,bsocket server,std::string fileName, int chunksize)
{
    /*Read input file*/
    cout << "Reading " << fileName << endl;
    ifstream fin(fileName.insert(0,fileDir), ios::binary | ios::ate);
    long filesize = fin.tellg();
    fin.seekg(0,ios::beg);
    cout << "Size of file is: " << filesize << endl;

    /*Define buffer*/
    unsigned char *buffer = new unsigned char[chunksize];
    cout << "Defined buffer" << endl;

    /*Send header first*/
    server.sendMessage((char*)header.c_str(),256); //TODO: make size dynamic
    cout << "Sending header.." << endl;
    usleep(100000);
    int sendData = 0;

    /*Read from file in chunks*/
    int i = 1;
    while (fin.read((char*)buffer, chunksize))
    {   
        /*Send in socket*/
        sendData += chunksize;
        cout << "Send "<<sendData<< " bytes of data"<<endl;
        server.sendMessage((char*)buffer,chunksize);
        i++;

        /*If chunk is bigger than file truncate it*/
        if (i*chunksize>filesize){
            chunksize = filesize-(i-1)*chunksize;
            cout << "Truncating chunksize to " << chunksize << endl;
        }

        usleep(10000);  //Wait for debug
    }

    cout << "Finished sending all file-data" << endl;

    /*Close file handle*/
    fin.close();

    return 1;
}

std::string fileHandler::getType(std::string str)
{
    size_t i = str.rfind('.', str.length());
    if (i != string::npos) {
        return(str.substr(i+1, str.length() - i));
    }
    return("");
}
