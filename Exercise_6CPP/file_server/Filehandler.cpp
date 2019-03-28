#include "/root/Git/IKN/Exercise_6CPP/file_server/Filehandler.h"
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include "/root/Git/IKN/Exercise_6CPP/file_server/Serversocket.h"
#include <unistd.h>
#include <string.h>

using namespace std;

Filehandler::Filehandler()
{
    updateFilesInCurrentFolder();
}


void Filehandler::printFiles()
{
    for (vector<string>::iterator it = files.begin(); it != files.end(); ++it)
        cout << *it << endl;
}

int Filehandler::updateFilesInCurrentFolder()
{
    DIR* dirp = opendir(fileDir.c_str());
    struct dirent * dp;
    while((dp=readdir(dirp)) != NULL)
    {
        files.push_back(dp->d_name);
    }
    closedir(dirp);
}

bool Filehandler::checkForFile(const std::string str){
    if (std::find(files.begin(), files.end(), str) != files.end())
    {
        return true;
    }
    return false;
}

int Filehandler::getSize(std::string str)
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

int Filehandler::sendFile(string header,Serversocket server,std::string fileName, int chunksize, int udelay)
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
    server.sendMessage((char*)header.c_str(),strlen(header.c_str())); //Can use strlen here because header is a normal null-terminated string
    cout << "Sending header.." << endl;
    usleep(udelay);
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

        /*If chunk is bigger than file then truncate it*/
        if (i*chunksize>filesize){
            chunksize = filesize-(i-1)*chunksize;
            cout << "Truncating chunksize to " << chunksize << endl;
        }

        usleep(udelay);  //Wait for debugging
    }

    cout << "Finished sending all file-data" << endl;

    /*Close file handle*/
    fin.close();

    return 1;
}

std::string Filehandler::getType(std::string str)
{
    size_t i = str.rfind('.', str.length());
    if (i != string::npos) {
        return(str.substr(i+1, str.length() - i));
    }
    return("");
}
