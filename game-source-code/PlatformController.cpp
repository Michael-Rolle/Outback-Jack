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

void PlatformController::spawnPlatformRow(unsigned int gameRow, bool right)
{
//
}

vector<float> PlatformController::getPlatformPositions(const unsigned int row)
{
    return plaformRows.at(row-1).platformPositions();
}
