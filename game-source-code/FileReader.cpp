#include "FileReader.h"

FileReader::FileReader(const string& filePath)
{
    this->filePath = filePath;
}

string FileReader::read()
{
    auto file = ifstream{filePath};
    if(!file.is_open())
        throw "file cannot open";
    string content = "";
    file >> content;
    file.close();
    return content;
}

void FileReader::write(const string& input)
{
    auto file = ofstream{filePath};
    if(!file.is_open())
        throw "file cannot open";
    file << input;
    file.close();
}
