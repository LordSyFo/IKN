#include "filehandler.h"
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>

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

string fileHandler::openFile(string fileName)
{
    ifstream fin(fileName.insert(0,fileDir), ios::binary);
    stringstream sstr;
    sstr << fin.rdbuf();
    return sstr.str();
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
        string temp = openFile(str);
        return temp.length();
    }
    return -1;
}

int fileHandler::makeFileFromBinary(file_message fm, string fileName)
{
    /*Make file name with correct file extension*/
    stringstream sstr;
    sstr << fileName << "." << fm.fileType;
    ofstream out(sstr.str(), ios::binary);

    /*Append binary file data to file*/
    out << fm.data;

    if (out.tellp() == fm.fileSize)
    {
        cout << "Succesfully made " << fileName << "." << fm.fileType << "!" << endl;
        return 1;
    } else {
        cout << "Failed making " << fileName << "." << fm.fileType << "!" << endl;
        cout << "Missed " << fm.fileSize-out.tellp() << " bytes.. Try again!" << endl;
        return 0;
    }
}

std::string fileHandler::getType(std::string str)
{
    size_t i = str.rfind('.', str.length());
    if (i != string::npos) {
        return(str.substr(i+1, str.length() - i));
    }
    return("");
}
