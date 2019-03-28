#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include <vector>
#include "Filehandler.h"

class Message
{
public:
    Message();
    Message(Filehandler,std::string, int);
    void printAllMessages();
    void printMessage(int i);
    int getNumberOfMessages();
    std::vector<char*> getMessages();
    file_message parseFileMessage(std::vector<char *>message);
    std::string getHeader();
    bool hasDigit(const std::string&);

private:
    std::vector<char*>_messages;
    file_message _fmess;
    Filehandler test;

    /*Private methods*/
    std::string findField(const std::string field, std::string mes);
};

#endif // MESSAGE_H
