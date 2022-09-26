#include "PlatformController.h"
#include "PlatformRow.h"
#include <vector>

using namespace std;

PlatformController::PlatformController(sf::Texture* texture)
{
    bool direction = true;
    for(int i = 0; i < 4; i++)
    {
        auto platformRow = PlatformRow(texture, 6, 50, i+2, direction);
        direction = !direction;
        platformRows.push_back(platformRow);
    }
}

PlatformController::PlatformController(const PlatformController& controller)
{
    this->platformRows = controller.platformRows;
}

PlatformController PlatformController::operator= (const PlatformController& platformController)
{
    auto controller = PlatformController{platformController};
    return controller;
}

void PlatformController::changePlatformRowColour(unsigned int row, sf::Texture* texture)
{
    platformRows.at(row-1).changeColour(texture);
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

vector<float> PlatformController::getPlatformPositions(const unsigned int row)
{
    auto positions = platformRows.at(row-1).platformPositions();
    return positions;
}
