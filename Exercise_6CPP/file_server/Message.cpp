#include "Message.h"
#include <string>
#include <sstream>
#include "Filehandler.h"
#include <cmath>
#include <iostream>
#include <string.h>
#include <cctype>
#include <algorithm>

using namespace std;

Message::Message()
{
    cout << "Making default message object.." << endl;
    cout << "-------------------------------" << endl;
    cout << "Adding N/A to fields..........." << endl;
    char* header = new char[256];   //Maybe truncate?
    sprintf(header,
            "Size:N/A\nType:N/A\nName:N/A\nChunksize:N/A\n");
    _messages.push_back(header);
    cout << "Succesfully made not available message!" << endl;
}

Message::Message(Filehandler file,string fileName, int sendLength)
{
    if (!file.checkForFile(fileName))
    {
        cout << fileName << " Doesnt exist!" << endl;
        delete this;
        return;
    }

    /*Append header to message vector*/
    char* header = new char[256];   //Maybe truncate?
    sprintf(header,
            "Size:%d\nType:%s\nName:%s\nChunksize:%d\n",
            file.getSize(fileName),
            file.getType(fileName).c_str(),
            fileName.c_str(),
            sendLength);
    _messages.push_back(header);

    cout << "File size: " << file.getSize(fileName) << endl;
    cout << "Message size: " << _messages.size() << endl;
}

void Message::printMessage(int i)
{
    if (i < _messages.size())
    {
        cout << _messages[i] << endl;
    }
    else
    {
        cout << "Out of index!" << endl;
        return;
    }
}

int Message::getNumberOfMessages()
{
    return _messages.size();
}

void Message::printAllMessages()
{
    for(auto i : _messages) {
        cout << i << '\n';
    }
}

file_message Message::parseFileMessage(vector<char*>message)
{
    file_message tmpmss;

    cout << message[0] << endl;

    /*Find and add filesize*/
    string size = findField("Size:",message[0]);
    string chunkSize = findField("Chunksize:",message[0]);

    /*Check if strings has digits to avoid exception thrown*/
    if (hasDigit(size))
    {
        //cout << size << " has digits!" << endl;
        tmpmss.fileSize = stoi(size);
    } else {
        //cout << size << " doesnt have digits!" << endl;
        tmpmss.fileSize = -1;
    }

    if (hasDigit(chunkSize))
    {
        //cout << chunkSize << " has digits!" << endl;
        tmpmss.chunkSize = stoi(chunkSize);
    } else {
        //cout << chunkSize << " doesnt have digits!" << endl;
        tmpmss.chunkSize = -1;
    }

    tmpmss.fileType = findField("Type:",message[0]);
    tmpmss.fileName = findField("Name:",message[0]);

    return tmpmss;
}

string Message::getHeader()
{
    return _messages[0];
}

vector<char*> Message::getMessages()
{
    return _messages;
}

string Message::findField(const string field, string mes) {
    size_t start = mes.find(field);
    size_t end = mes.find('\n', start);
    return mes.substr(start + field.length(),end - (start + field.length()));
}

bool Message::hasDigit(const std::string& s)
{
    return std::any_of(s.begin(), s.end(), ::isdigit);
}
