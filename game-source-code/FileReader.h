#ifndef FILEREADER_H
#define FILEREADER_H
#include <fstream>
#include <string>
#include <iostream>

using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;

/*! Class capable of reading from and writing to a text file. Used here in the context of tracking a high score for the game. */

class FileReader
{
    public:
        FileReader(const string& filePath);
        string read(); /*!< Returns a string containing the contents of a text file. Reads all the contents of the text file.*/
        void write(const string& input); /*!< Takes a constant reference to a string and writes its data to a text file. */

    private:
        string filePath;
};

#endif // FILEREADER_H
