#ifndef POINTCOLLISIONS_H
#define POINTCOLLISIONS_H
#include <SFML/Graphics.hpp>
#include "EnemyController.h"
#include "FishController.h"
#include "Jack.h"
#include "Score.h"
#include "GameSounds.h"

class PointCollisions
{
    public:
        PointCollisions(float enemyWidth);
        PointCollisions(){};
        void update(Jack& player, Score& score, FishController& fishRow, GameSounds& gameSounds);

    private:
        float fishWidth;
};

#endif // POINTCOLLISIONS_H
