#ifndef FILEREADER_H
#define FILEREADER_H
#include <fstream>
#include <string>
#include <iostream>

using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;

class FileReader
{
    public:
        FileReader(const string& filePath);
        string read();
        void write(const string& input);

    private:
        string filePath;
};

#endif // FILEREADER_H
