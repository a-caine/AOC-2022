#include "filereader.h"

// Simply open the file specified in the constructor
FileReader::FileReader(std::string fileName) {
    openFile(fileName);
}

// Opens the fstream using the file name specified
void FileReader::openFile(std::string fileName) {
    fileStream.open(fileName);
}

// Read a line from the file and return true for success, and false for failure
bool FileReader::readLine(std::string *string) {
    if (std::getline(fileStream, *string)) return true;
    else return false;
}

// Closes the file stream, allowing for more files to be read
void FileReader::closeFile() {
    fileStream.close();
}