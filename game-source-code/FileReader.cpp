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
    auto file = ifstream{filePath};
    if(!file.is_open())
        throw "file cannot open";
    //char c;
    string content = "";
    //while(!file.eof())
    //{
    //    file.get(c);
    //    content += c;
    //}
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
