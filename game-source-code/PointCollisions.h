#ifndef POINTCOLLISIONS_H
#define POINTCOLLISIONS_H
#include <SFML/Graphics.hpp>
#include "EnemyController.h"
#include "Jack.h"
#include "Score.h"

class PointCollisions
{
    public:
        PointCollisions(float enemyWidth, float enemySpeed);
        PointCollisions(){};
        void update(Jack& player, Score& score, EnemyController& friends);

    private:
        float enemyWidth;
        float enemySpeed;
};

#endif // POINTCOLLISIONS_H
