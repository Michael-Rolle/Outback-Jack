#ifndef POINTCOLLISIONS_H
#define POINTCOLLISIONS_H
#include <SFML/Graphics.hpp>
#include "EnemyController.h"
#include "FishController.h"
#include "Jack.h"
#include "Score.h"
#include "GameSounds.h"

/*!
Checks if the player collides with a fish, adding to their score and playing a sound. The fish is then removed.
*/

class PointCollisions
{
    public:
        PointCollisions(float enemyWidth);
        PointCollisions(){};
        void update(Jack& player, Score& score, FishController& fishRow, GameSounds& gameSounds);
        /*!< Checks for a collision occuring. Takes in the respective Player, a FishController to access the respective fish, a Score object to update the players' score and a GameSounds object to
             play a sound when the player collides with a fish. Parameters do not allow for the collision detection of multiple players. */

    private:
        float fishWidth;
};

#endif // POINTCOLLISIONS_H
