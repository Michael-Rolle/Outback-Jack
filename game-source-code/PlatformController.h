#ifndef PLATFORMCONTROLLER_H
#define PLATFORMCONTROLLER_H
#include "PlatformRow.h"
#include <vector>

using namespace std;

class PlatformController
{
    public:
        PlatformController(sf::Texture* texture);
        PlatformController(){};
        void changePlatformRowColour(unsigned int row, sf::Texture* texture, bool original); //enter a row num from 1 to 4
        void update(float deltaTime);
        void draw(sf::RenderWindow& window);
        bool allPlatformsNewColour();
        PlatformRow* getPlatformRow(const unsigned int row); //enter a row num from 1 to 4
        vector<float> getPlatformPositions(const unsigned int row); //enter a row num from 1 to 4

    private:
        vector<PlatformRow> platformRows;
};

#endif // PLATFORMCONTROLLER_H
