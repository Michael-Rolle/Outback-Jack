#include "PlatformRow.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Platform.h"

using namespace std;

PlatformRow::PlatformRow(sf::Texture* texture, const unsigned int numPlatforms, const float spacing, const unsigned int gameRow, const bool movingRight)
{
    this->numPlatforms = numPlatforms;
    this->spacing = spacing;
    this->gameRow = gameRow;
    this->movingRight = movingRight;
    for(int i = 0; i < (int)numPlatforms; i++)
    {
        auto platform = Platform{texture, 100.0f, movingRight, gameRow};
        if(movingRight) //ensure the first element in the vector is the left most element
            platform.setPositionX(platform.width()/2.0f + i*(spacing+platform.width()));
        else
            platform.setPositionX(1920 - ((numPlatforms-1-i)*(spacing+platform.width())+platform.width()/2.0f));
        platforms.push_back(platform);
    }
    this->isOriginalColour = true;
    this->canChangeColour = true;
}

vector<float> PlatformRow::platformPositions()
{
    vector<float> positions;
    for(auto& platform : platforms)
    {
        positions.push_back(platform.getPositionX());
    }
    return positions;
}

void PlatformRow::changeDirection()
{
    movingRight = !movingRight;
    for(auto& platform : platforms)
        platform.changeDirection();
}

void PlatformRow::changeColour(sf::Texture* texture, bool original)
{
    isOriginalColour = original;
    for(auto& platform : platforms)
        platform.changeColour(texture);
}

void PlatformRow::update(float deltaTime)
{
    for(auto& platform : platforms)
    {
        if(platform.getPositionX()+platform.width()/2.0f <= 0 && !movingRight)
            platform.setPositionX(1920+platform.width()/2.0f);
        else if(platform.getPositionX()-platform.width()/2.0f >= 1920 && movingRight)
            platform.setPositionX(0-platform.width()/2.0f);

        platform.update(deltaTime);
    }
}

void PlatformRow::draw(sf::RenderWindow& window)
{
    for(auto& platform : platforms)
        platform.draw(window);
}
