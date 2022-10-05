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
        vector<float> fishPositions();
        void update();
        void draw(sf::RenderWindow& window);
    private:
        void newFishRow();

    private:
        vector<Enemy> fishRow;
        unsigned int gameRow;
        unsigned int numFish;
        float spacing;
        bool movingRight;
        sf::Texture fishText;
};

#endif // FISHCONTROLLER_H
