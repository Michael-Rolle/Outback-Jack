#include "PlatformRow.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Platform.h"

PlatformRow::PlatformRow(sf::Texture* texture, const unsigned int numPlatforms, const float spacing, const unsigned int gameRow, const bool movingRight)
{
    this->numPlatforms = numPlatforms;
    this->spacing = spacing;
    this->gameRow = gameRow;
    this->movingRight = movingRight;
    for(int i = 0; i < numPlatforms; i++)
    {
        auto platform = Platform()
        platforms.push_back()
    }
}

vector<float> PlatformRow::platformPositions()
{

}

void PlatformRow::changeDirection()
{

}

void PlatformRow::update(float deltaTime)
{

}

void PlatformRow::draw(sf::RenderWindow& window)
{

}
