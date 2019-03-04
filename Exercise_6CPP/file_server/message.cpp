#include "message.h"
#include <string>
#include <sstream>
#include "filehandler.h"
#include <cmath>
#include <iostream>
#include <string.h>

using namespace std;

message::message()
{
    cout << "Making default message object.." << endl;
}

message::message(fileHandler file, string fileName, int sendLength)
{
    if (!file.checkForFile(fileName))
    {
        cout << fileName << " Doesnt exist!" << endl;
        delete this;
        return;
    }

    /*Append header to message vector*/
    char* header = new char[256];
    sprintf(header,
            "Size:%d\nType:%s\n",
            file.getSize(fileName),
            file.getType(fileName).c_str());
    _messages.push_back(header);

    /*Append files in sentLengths*/
    size_t len = file.getSize(fileName);
    char* fileStr = file.openFile(fileName);
    char buffer[1000];
    int catted = 0;

    while(catted < len)
    {
        if (catted+1000 > len)
        {
        memcpy(buffer, fileStr+catted,sendLength-(catted+sendLength-len));
        _messages.push_back(buffer);
        catted += sendLength-(catted+sendLength-len);
        } else
        {
        memcpy(buffer,fileStr+catted,sendLength);
        _messages.push_back(buffer);
        catted += 1000;
        }
        cout << "Catted " << catted << " / " << len << endl;
    }

    cout << "File size: " << len << endl;
    cout << "Message size: " << _messages.size() << endl;
}

void message::printMessage(int i)
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

int message::getNumberOfMessages()
{
    return _messages.size();
}

void message::printAllMessages()
{
    for(auto i : _messages) {
        cout << i << '\n';
    }
}

file_message message::parseFileMessage(vector<char*>message)
{
    file_message tmpmss;

    cout << message[0] << endl;

    /*Find and add filesize*/
    tmpmss.fileSize = stoi(findField("Size:",message[0]));
    tmpmss.fileType = findField("Type:",message[0]);

    return tmpmss;
}

vector<char*> message::getMessages()
{
    return _messages;
}

string message::findField(const string field, string mes) {
    size_t start = mes.find(field);
    size_t end = mes.find('\n', start);
    return mes.substr(start + field.length(),end - (start + field.length()));
}
