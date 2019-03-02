#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <vector>
#include <string>

class fileHandler
{
public:
    fileHandler();
    void printFiles();
    int updateFilesInCurrentFolder();
    bool checkForFile(const std::string str);
    std::string openFile(const std::string);
    int getSize(std::string str);
    int makeFileFromString(std::string binary, std::string type); TODO!!
     

private:
    std::vector<std::string> files;
    std::string fileDir = "/root/Git/IKN/Exercise_6CPP/file_server/Files/"; //Should be specified when creating object

};

#endif // FILEHANDLER_H
