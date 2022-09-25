#ifndef PLATFORMROW_H
#define PLATFORMROW_H
#include "Platform.h"
#include <vector>

using namespace std;

class PlatformRow
{
    public:
        PlatformRow(sf::Texture* texture, const unsigned int numPlatforms, const float spacing, const unsigned int gameRow, const bool movingRight);
        vector<float> platformPositions();
        bool isMovingRight(){ return movingRight; }
        Platform getPlatform(const unsigned int platformNum){ return platforms.at(platformNum-1); } //enter a number from 1 to numPlatforms
        void changeDirection();
        void update(float deltaTime);
        void draw(sf::RenderWindow& window);

    private:
        vector<Platform> platforms;
        unsigned int gameRow;
        bool movingRight;
        float spacing;
        unsigned int numPlatforms;
};

#endif // PLATFORMROW_H
