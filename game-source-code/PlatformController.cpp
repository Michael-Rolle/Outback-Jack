#include "PlatformController.h"
#include "PlatformRow.h"
#include <vector>

using namespace std;

PlatformController::PlatformController(sf::Texture* texture)
{
    bool direction = true;
    for(int i = 0; i < 4; i++)
    {
        auto platformRow = PlatformRow{texture, 6, 50, (unsigned int)(i+2), direction};
        direction = !direction;
        platformRows.push_back(platformRow);
    }
}

void PlatformController::changePlatformRowColour(unsigned int row, sf::Texture* texture, bool original)
{
    platformRows.at(row-1).changeColour(texture, original);
}

bool PlatformController::allPlatformsNewColour()
{
    for(auto& platformRow : platformRows)
    {
        if(platformRow.isOriginalColour)
            return false;
    }
    return true;
}

void PlatformController::update(float deltaTime)
{
    for(auto& platformRow : platformRows)
        platformRow.update(deltaTime);
}

void PlatformController::draw(sf::RenderWindow& window)
{
    for(auto& platformRow : platformRows)
        platformRow.draw(window);
}

PlatformRow* PlatformController::getPlatformRow(const unsigned int row)
{
    return &platformRows.at(row-1);
}

vector<float> PlatformController::getPlatformPositions(const unsigned int row)
{
    auto positions = platformRows.at(row-1).platformPositions();
    return positions;
}
