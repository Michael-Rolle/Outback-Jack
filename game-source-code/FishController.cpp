#include "FishController.h"
#include <cstdlib>

FishController::FishController(sf::Texture* fishTexture, const unsigned int numFish, const float spacing)
{
    this->fishText = *fishTexture;
    this->spacing = spacing;
    auto direction = rand()%2;
    movingRight = (bool)direction;
    gameRow = rand()%4+2; //generates a random number between 2 and 5
    this->numFish = numFish;
    for(int i = 0; i < (int)numFish; i++)
    {
        auto fish = Enemy{fishTexture, 200.0f, movingRight, gameRow};
        if(movingRight) //ensure the first element in the vector is the left most element
            fish.setPositionX(pos - ((numFish-1-i)*(spacing+enemy.width())+enemy.width()/2.0f));
        else
            fish.setPositionX(pos + enemy.width()/2.0f + i*(spacing+enemy.width()));
        fishRow.push_back(fish);
    }
}

void FishController::newFishRow()
{
    fishRow.erase();
    auto direction = rand()%2;
    gameRow = rand()%4+2; //generates a random number between 2 and 5
    for(int i = 0; i < numFish; i++)
    {
        auto fish = Enemy{fishText, 200.0f, (bool)direction, gameRow};
        fishRow.push_back(fish);
    }
}

vector<float> FishController::fishPositions()
{
    return fishRow.enemyPositions();
}

void FishController::update(float deltaTime)
{
    if(movingRight && fishRow.front().getPositionX() >= 1920.0f)
}

void FishController::draw(sf::RenderWindow& window)
{
    for(auto& fish: fishRow)
        fish.draw(window);
}
