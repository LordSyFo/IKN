#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <vector>
#include <string>
#include "Serversocket.h"

typedef struct file_message
{
    int fileSize = 0;
    std::string fileType;
    std::string fileName;
    int chunkSize = 0;
} file_message;

class Filehandler
{
public:
    Filehandler();
    void printFiles();
    int updateFilesInCurrentFolder();
    bool checkForFile(const std::string str);
    int getSize(std::string str);
    std::string getType(std::string str);
    int sendFile(std::string header,
                 Serversocket server,
                 std::string fileName,
                 int chunksize,
                 int udelay);

private:
    std::vector<std::string> files;
    std::string fileDir = "/root/Git/IKN/Exercise_6CPP/file_server/Files/"; //Should be specified when creating object
    long filesize_;

};

#endif // FILEHANDLER_H
