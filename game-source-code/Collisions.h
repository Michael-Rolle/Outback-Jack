#ifndef COLLISIONS_H
#define COLLISIONS_H
#include <SFML/Graphics.hpp>
#include "GameSounds.h"
#include "PlatformController.h"
#include "Jack.h"
#include "Tent.h"
#include "Score.h"

/*! Responsible for checking the player lands on a platform and then updating the colour of the platform to reflect this.
    If the player is not on a platform the collisions class is responsible for killing the player. The player can earn
    points for landing on platforms and the platforms only change colour if the tent is not built. The player moves with
    the platform if they stand still on it. A sound is played when the player lands on a platform. Also checks if the
    player is within the safe zone. */

class Collisions
{
    public:
        Collisions(float platformWidth, float platformSpeed);
        Collisions(){};
        void update(Jack& player, sf::Texture* deathTexture, PlatformController& platforms, sf::Texture* originalColour, sf::Texture* newColour, Tent& tent, Score& score, GameSounds& gameSounds); /*!<
        Checks for a collision occuring. Takes in the respective Player, a texture to update the player with
        if they die, a PlatformController to access the respective platforms, two textures to alternate between depending on if
        the platform has been landed on, a Tent object to track the construction of the tent, a Score object to update the
        players' score and a GameSounds object to play a sound when the player lands on a platform. Parameters do not allow for
        the collision detection of multiple players. */

    private:
        float platformWidth;
        float platformSpeed;
};

#endif // COLLISIONS_H
