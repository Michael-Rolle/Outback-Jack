#ifndef ENEMYCOLLISIONS_H
#define ENEMYCOLLISIONS_H
#include <SFML/Graphics.hpp>
#include "EnemyController.h"
#include "Jack.h"
#include "Kangaroo.h"

class EnemyCollisions
{
    public:
        EnemyCollisions(float enemyWidth, float enemySpeed);
        EnemyCollisions(){};
        void update(Jack& player, sf::Texture* deathTexture, EnemyController& enemies, Kangaroo& kangaroo);

    private:
        float enemyWidth;
        float enemySpeed;
};

#endif // ENEMYCOLLISIONS_H
