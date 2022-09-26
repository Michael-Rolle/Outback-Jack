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
    for(int i = 0; i < numPlatforms; i++)
    {
        auto platform = Platform(texture, 100.0f, movingRight, gameRow);
        if(movingRight) //ensure the first element in the vector is the left most element
            platform.setPositionX(platform.width()/2.0f + i*(spacing+platform.width()));
        else
            platform.setPositionX(1920 - ((numPlatforms-1-i)*(spacing+platform.width())+platform.width()/2.0f));
        platforms.push_back(platform);
    }
}

PlatformRow::PlatformRow(const PlatformRow& platformRow)
{
    this->numPlatforms = platformRow.numPlatforms;
    this->gameRow = platformRow.gameRow;
    this->movingRight = platformRow.movingRight;
    this->platforms = platformRow.platforms;
    this->spacing = platformRow.spacing;
}

PlatformRow& PlatformRow::operator= (const PlatformRow& platformRow)
{
    auto platformRow_ = PlatformRow{platformRow};
    return platformRow_;
}

vector<float> PlatformRow::platformPositions()
{
    auto positions = vector<float>(numPlatforms);
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

/*void PlatformRow::update(float deltaTime)
{
    if(platforms.front().getPositionX()-platforms.front().width()/2.0f <= 0 && !movingRight)
        changeDirection();
    else if(platforms.back().getPositionX()+platforms.back().width()/2.0f >= 1920 && movingRight)
        changeDirection();
    for(auto& platform : platforms)
    {
        platform.update(deltaTime);
    }
}*/

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
