#ifndef ENEMYCOLLISIONS_H
#define ENEMYCOLLISIONS_H
#include <SFML/Graphics.hpp>
#include "EnemyController.h"
#include "Jack.h"
//#include "Tent.h"

class EnemyCollisions
{
    public:
        EnemyCollisions(float enemyWidth, float enemySpeed);
        EnemyCollisions(){};
        void update(Jack& player, sf::Texture* deathTexture, EnemyController& enemies);

    private:
        float enemyWidth;
        float enemySpeed;
};

#endif // ENEMYCOLLISIONS_H
