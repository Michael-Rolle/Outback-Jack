#ifndef ENEMYCOLLISIONS_H
#define ENEMYCOLLISIONS_H
#include <SFML/Graphics.hpp>
#include "EnemyController.h"
#include "Jack.h"
#include "Kangaroo.h"

/*!
Checks if the player collides with an Enemy, killing the player and subsequently ending the game. Note: a Kangaroo object
is treated exactly as an Enemy object.
*/

class EnemyCollisions
{
    public:
        EnemyCollisions(float enemyWidth, float enemySpeed);
        EnemyCollisions(){};
        void update(Jack& player, sf::Texture* deathTexture, EnemyController& enemies, Kangaroo& kangaroo); /*!< Updates to
            check if the player has collided with an enemy. Parameters are only capable of checking one player at a time.
            Takes in a player and a texture to update the player with if they die and an EnemyController object and a Kangaroo
            object to determine the positions of the enemies.
          */

    private:
        float enemyWidth;
        float enemySpeed;
};

#endif // ENEMYCOLLISIONS_H
