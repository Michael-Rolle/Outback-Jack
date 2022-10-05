#include "FishController.h"
#include <cstdlib>

FishController::FishController(sf::Texture* fishTexture, unsigned int numFish)
{
    auto direction = rand()%2;
    gameRow = rand()%4+2; //generates a random number between 2 and 5
    this->numFish = numFish;
    for(int i = 0; i < (int)numFish; i++)
    {
        auto fish = Enemy{fishTexture, 200.0f, (bool)direction, gameRow};
        fishRow.push_back(fish);
    }
}

void FishController::newFishRow()
{
    fishRow.erase();
}

vector<float> FishController::fishPositions()
{
    return fishRow.enemyPositions();
}

void FishController::update(float deltaTime)
{
    if(fishRow.movingRight && fishRow.front().getPositionX() >= 1920.0f)
}

void FishController::draw(sf::RenderWindow& window)
{
    fishRow.draw(window);
}
