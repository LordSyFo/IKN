#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include <vector>
#include "filehandler.h"

typedef struct file_message
{
    int fileSize = 0;
    std::string data;
} file_message;

class message
{
public:
    message(fileHandler file, std::string fileName,int sendLength);
    void printAllMessages();
    void printMessage(int i);
    int getNumberOfMessages();
    std::vector<std::string> getMessages();
    file_message parseFileMessage(std::vector<std::string>message);

private:
    std::vector<std::string>_messages;
    file_message _fmess;

    /*Private methods*/
    std::string findField(const std::string field, std::string mes);
};

#endif // MESSAGE_H
