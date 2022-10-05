#ifndef FISHCONTROLLER_H
#define FISHCONTROLLER_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemy.h"

using std::vector;

class FishController
{
    public:
        FishController(sf::Texture* fishTexture, unsigned int numFish);
        vector<float> fishPositions();
        void update();
        void draw(sf::RenderWindow& window);
    private:
        void newFishRow();

    private:
        vector<Enemy> fishRow;
        unsigned int gameRow;
        unsigned int numFish;
};

#endif // FISHCONTROLLER_H
