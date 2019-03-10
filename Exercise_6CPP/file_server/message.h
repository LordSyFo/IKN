#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include <vector>
#include "filehandler.h"

class message
{
public:
    message();
    message(fileHandler,std::string, int);
    void printAllMessages();
    void printMessage(int i);
    int getNumberOfMessages();
    std::vector<char*> getMessages();
    file_message parseFileMessage(std::vector<char *>message);
    std::string getHeader();
    bool hasDigit(std::string);

private:
    std::vector<char*>_messages;
    file_message _fmess;
    fileHandler test;

    /*Private methods*/
    std::string findField(const std::string field, std::string mes);
};

#endif // MESSAGE_H
