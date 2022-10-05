#include "FishController.h"
#include <cstdlib>

FishController::FishController(sf::Texture* fishTexture, const unsigned int numFish, const float spacing)
{
    this->fishText = *fishTexture;
    this->spacing = spacing;
    auto direction = rand()%2;
    movingRight = (bool)direction;
    gameRow = (unsigned int)(rand()%4+2); //generates a random number between 2 and 5
    this->numFish = numFish;
    for(int i = 0; i < (int)numFish; i++)
    {
        auto fish = new Enemy{fishTexture, 200.0f, movingRight, gameRow};
        if(movingRight) //ensure the first element in the vector is the left most element
            fish->setPositionX(1920.0f - ((numFish-1-i)*(spacing+fish->width())+fish->width()/2.0f));
        else
            fish->setPositionX(fish->width()/2.0f + i*(spacing+fish->width()));
        fishRow.push_back(fish);
    }
}

void FishController::newFishRow()
{
    fishRow.clear();
    auto direction = rand()%2;
    movingRight = (bool)direction;
    gameRow = rand()%4+2; //generates a random number between 2 and 5
    for(int i = 0; i < (int)numFish; i++)
    {
        auto fish = new Enemy{&fishText, 200.0f, movingRight, gameRow};
        if(movingRight) //ensure the first element in the vector is the left most element
            fish->setPositionX(1920.0f - ((numFish-1-i)*(spacing+fish->width())+fish->width()/2.0f));
        else
            fish->setPositionX(fish->width()/2.0f + i*(spacing+fish->width()));
        fishRow.push_back(fish);
    }
}

vector<float> FishController::fishPositions()
{
    vector<float> positions;
    for(auto& fish : fishRow)
        positions.push_back(fish->getPositionX());
    return positions;
}

void FishController::removeFish(unsigned int fishNum)
{
    if(fishNum < 1 || fishNum > fishRow.size())
        throw "Invalid index";
    delete fishRow.at(fishNum-1);
    fishRow.at(fishNum-1) = nullptr;
}

void FishController::update(float deltaTime)
{
    bool emptyRow = true;
    for(int i = 0; i < (int)numFish; i++)
    {
        if(fishRow.at(i) != nullptr)
            emptyRow = false;
    }
    if(emptyRow)
        newFishRow();

    for(auto& fish : fishRow)
        fish->update(deltaTime);
}

void FishController::draw(sf::RenderWindow& window)
{
    for(auto& fish: fishRow)
    {
        if(fish != nullptr)
            fish->draw(window);
    }
}
