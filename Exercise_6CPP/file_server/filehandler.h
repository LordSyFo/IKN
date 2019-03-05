#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <vector>
#include <string>
#include "bsocket.h"

typedef struct file_message
{
    int fileSize = 0;
    std::string fileType;
    char* fileName;
} file_message;

class fileHandler
{
public:
    fileHandler();
    void printFiles();
    int updateFilesInCurrentFolder();
    bool checkForFile(const std::string str);
    char* openFile(const std::string);
    int getSize(std::string str);
    std::string getType(std::string str);
    int sendFile(std::string header,bsocket server,std::string fileName, int chunksize);

private:
    std::vector<std::string> files;
    std::string fileDir = "/root/Git/IKN/Exercise_6CPP/file_server/Files/"; //Should be specified when creating object
    long filesize_;

};

#endif // FILEHANDLER_H
