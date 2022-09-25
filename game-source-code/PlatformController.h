#ifndef PLATFORMCONTROLLER_H
#define PLATFORMCONTROLLER_H
#include "PlatformRow.h"
#include <vector>

using namespace std;

class PlatformController
{
    public:
        PlatformController();
        void update(float deltaTime);
        void draw(sf::RenderWindow& window);
        void spawnPlatformRow(unsigned int gameRow, bool right);

    private:
        vector<PlatformRow> platformRows;
};

#endif // PLATFORMCONTROLLER_H
