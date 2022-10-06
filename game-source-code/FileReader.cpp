#include "FileReader.h"

FileReader::FileReader(const string& filePath)
{
    /*file.open(filePath, ios::in | ios::out);
    if(!file.is_open())
        throw "cannot open file.";*/
    this->filePath = filePath;
}

string FileReader::read()
{
    char c;
    string content = "";
    while(!file.eof())
    {
        file.get(c);
        content += c;
    }
    //file >> content;
    return content;
}

void FileReader::write(const string& input)
{
    file.clear();
    file << input;
}
