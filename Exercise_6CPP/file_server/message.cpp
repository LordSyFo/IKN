#include "message.h"
#include <string>
#include <sstream>
#include "filehandler.h"
#include <cmath>
#include <iostream>

using namespace std;

message::message()
{}

message::message(fileHandler file, string fileName, int sendLength)
{
    if (!file.checkForFile(fileName))
    {
        cout << fileName << " Doesnt exist!" << endl;
        delete this;
        return;
    }

    /*Append header to message vector*/
    stringstream header;
    header << "Size:" << file.getSize(fileName) << '\n';
    header << "Type:" << file.getType(fileName) << '\n';
    _messages.push_back(header.str());

    /*Append files in sentLengths*/
    size_t len = file.getSize(fileName);
    size_t iterations = ceil(len / sendLength); /*Round up*/
    string fileStr = file.openFile(fileName);

    for (size_t i = 0; i <= iterations*sendLength; i+= sendLength)
    {
        if (i + sendLength > len)
        {
            _messages.push_back(fileStr.substr(i, (size_t)len));
            //cout << "Inserted " << i << " to " << len << endl;
        } else
        {
            _messages.push_back(fileStr.substr(i, sendLength));
            //cout << "Inserted " << i << " to " << i + sendLength << endl;
        }
    }
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

file_message message::parseFileMessage(vector<std::string>message)
{
    file_message tmpmss;

    /*Find and add filesize*/
    tmpmss.fileSize = stoi(findField("Size:",message[0]));
    tmpmss.fileType = findField("Type:",message[0]);

    /*Parse all of data to one string and into file_message structure*/
    for (int i = 1; i < message.size(); i++)
    {
        tmpmss.data.append(message[i]);
    }

    return tmpmss;
}

vector<string> message::getMessages()
{
    return _messages;
}

string message::findField(const string field, string mes) {
    size_t start = mes.find(field);
    size_t end = mes.find('\n', start);
    return mes.substr(start + field.length(),end - (start + field.length()));
}
