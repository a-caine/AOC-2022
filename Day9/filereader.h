#ifndef FILEREADER_H
#define FILEREADER_H

#include <fstream>
#include <string>

class FileReader {

    private:
        std::fstream fileStream;

    public:
        FileReader(std::string fileName);
        void openFile(std::string fileName);
        bool readLine(std::string *string);
        void closeFile();
};
#endif