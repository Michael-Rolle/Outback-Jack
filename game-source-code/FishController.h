#ifndef FISHCONTROLLER_H
#define FISHCONTROLLER_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemy.h"

using std::vector;

class FishController
{
    public:
        FishController(sf::Texture* fishTexture, const unsigned int numFish, const float spacing);
        FishController(){}
        vector<float> fishPositions();
        unsigned int row(){ return gameRow; }
        Enemy getFish(unsigned int fishNum){ return *fishRow.at(fishNum-1); } //enter a value from 1 to numFish
        void removeFish(unsigned int fishNum);
        void update(float deltaTime);
        void draw(sf::RenderWindow& window);
    private:
        void newFishRow();

    private:
        vector<Enemy*> fishRow;
        unsigned int gameRow;
        unsigned int numFish;
        float spacing;
        bool movingRight;
        sf::Texture fishText;
};

#endif // FISHCONTROLLER_H
