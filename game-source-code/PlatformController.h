#ifndef PLATFORMCONTROLLER_H
#define PLATFORMCONTROLLER_H
#include "PlatformRow.h"
#include <vector>

using namespace std;

class PlatformController
{
    public:
        PlatformController(sf::Texture* texture);
        PlatformController(const PlatformController& controller);
        PlatformController& operator= (const PlatformController& platformController);
        void update(float deltaTime);
        void draw(sf::RenderWindow& window);
        void spawnPlatformRow(unsigned int gameRow, bool right);
        PlatformRow getPlatformRow(const unsigned int row){ return platformRows.at(row-1); } //enter a row num from 1 to 4
        vector<float> getPlatformPositions(const unsigned int row); //enter a row num from 1 to 4

    private:
        vector<PlatformRow> platformRows;
};

#endif // PLATFORMCONTROLLER_H
