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
            "Size: %d\nType: %s\n",
            file.getSize(fileName),
            file.getType(fileName).c_str());
    _messages.push_back(header);

    /*Append files in sentLengths*/
    size_t len = file.getSize(fileName);
    size_t iterations = ceil(len / sendLength); /*Round up*/
    char* fileStr = file.openFile(fileName);
    char buffer[1001];
    cout << "Iterations: " << iterations << endl;

    for (size_t i = 0; i <= iterations*sendLength; i+= sendLength)
    {
        if (i+sendLength > len)
        {
            cout << "2Inserted " << i << " to " << i+sendLength-(i+sendLength-len) << endl;
            _messages.push_back(strncpy(buffer,fileStr+i,sendLength-(i+sendLength-len)));
        } else
        {
        _messages.push_back(strncpy(buffer,fileStr+i,sendLength));
        cout << "Inserted " << i << " to " << sendLength+i << endl;
        }
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

    char* buffer = new char[tmpmss.fileSize];

    /*Parse all of data to one string and into file_message structure*/
    for (int i = 1; i < message.size(); i++)
    {
        strcat(buffer,message[i]);
    }
    tmpmss.data = buffer;

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
