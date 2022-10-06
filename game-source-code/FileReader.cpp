#include "FileReader.h"

FileReader::FileReader(const string& filePath)
{
    file.open(filePath, ios::in | ios::out);
    if(!file.is_open())
        throw "cannot open file.";
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
    return content;
}

void FileReader::write(const string& input)
{
    file << input;
}
