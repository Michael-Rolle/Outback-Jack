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
        auto fish = new Enemy{fishTexture, 300.0f, movingRight, gameRow};
        if(!movingRight) //ensure the first element in the vector is the left most element
            fish->setPositionX(1920.0f + 400.0f + ((i)*(spacing+fish->width())+fish->width()/2.0f));
        else
            fish->setPositionX(-400.0f - fish->width()/2.0f - (numFish-1-i)*(spacing+fish->width()));
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
        auto fish = new Enemy{&fishText, 300.0f, movingRight, gameRow};
        if(!movingRight) //ensure the first element in the vector is the left most element
            fish->setPositionX(1920.0f + 400.0f + ((i)*(spacing+fish->width())+fish->width()/2.0f));
        else
            fish->setPositionX(-400.0f - fish->width()/2.0f - (numFish-1-i)*(spacing+fish->width()));
        fishRow.push_back(fish);
    }
}

vector<float> FishController::fishPositions()
{
    vector<float> positions;
    for(auto& fish : fishRow)
    {
        if(fish == nullptr)
            positions.push_back(-1);
        else
            positions.push_back(fish->getPositionX());
    }
    return positions;
}

void FishController::removeFish(unsigned int fishNum)
{
    if(fishNum < 1 || fishNum > fishRow.size())
        throw "Invalid index";
    /*if(fishRow.at(fishNum-1) == nullptr && !movingRight)
        removeFish(fishNum+1);
    if(fishRow.at(fishNum-1) == nullptr && movingRight)
        removeFish(fishNum-1);*/
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
    {
        if(fish != nullptr)
        {
            if(fish->getPositionX()+fish->width()/2.0f <= 0 && !movingRight)
                fish->setPositionX(1920+fish->width()/2.0f);
            else if(fish->getPositionX()-fish->width()/2.0f >= 1920 && movingRight)
                fish->setPositionX(0-fish->width()/2.0f);

            fish->update(deltaTime);
        }
    }
}

void FishController::draw(sf::RenderWindow& window)
{
    for(auto& fish: fishRow)
    {
        if(fish != nullptr)
            fish->draw(window);
    }
}
