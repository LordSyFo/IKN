#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <vector>
#include <string>

typedef struct file_message
{
    int fileSize = 0;
    std::string fileType;
    std::string data;
} file_message;

class fileHandler
{
public:
    fileHandler();
    void printFiles();
    int updateFilesInCurrentFolder();
    bool checkForFile(const std::string str);
    std::string openFile(const std::string);
    int getSize(std::string str);
    std::string getType(std::string str);
    int makeFileFromBinary(file_message fm, std::string fileName);

private:
    std::vector<std::string> files;
    std::string fileDir = "/root/Git/IKN/Exercise_6CPP/file_server/Files/"; //Should be specified when creating object

};

#endif // FILEHANDLER_H
