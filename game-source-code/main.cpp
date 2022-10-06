//#include "GameManager.h"
#include "FileReader.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    /*auto gameManager = GameManager();
    gameManager.run();
    return EXIT_SUCCESS;*/
    auto fileReader = FileReader{"resources/highscore.txt"};
    //fileReader.write(to_string(1000));
    cout << fileReader.read();
    fileReader.write("12");
    cout << fileReader.read();
    //cout << stoi(fileReader.read());
    //cout << stoi(fileReader.read());
    return 0;
}
