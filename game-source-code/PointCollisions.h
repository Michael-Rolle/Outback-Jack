#ifndef POINTCOLLISIONS_H
#define POINTCOLLISIONS_H
#include <SFML/Graphics.hpp>
#include "EnemyController.h"
#include "FishController.h"
#include "Jack.h"
#include "Score.h"

class PointCollisions
{
    public:
        PointCollisions(float enemyWidth);
        PointCollisions(){};
        //void update(Jack& player, Score& score, EnemyController& friends);
        void update(Jack& player, Score& score, FishController& fishRow);

    private:
        float fishWidth;
        //float enemySpeed;
};

#endif // POINTCOLLISIONS_H
