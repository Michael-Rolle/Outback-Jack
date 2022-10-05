#ifndef FISHCONTROLLER_H
#define FISHCONTROLLER_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemy.h"

using std::vector;

class FishController
{
    public:
        FishController(unsigned int numFish);
        void update();
        void draw();

    private:
        vector<Enemy> fish;
};

#endif // FISHCONTROLLER_H
