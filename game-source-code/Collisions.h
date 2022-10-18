#ifndef COLLISIONS_H
#define COLLISIONS_H
#include <SFML/Graphics.hpp>
#include "GameSounds.h"
#include "PlatformController.h"
#include "Jack.h"
#include "Tent.h"
#include "Score.h"

class Collisions
{
    public:
        Collisions(float platformWidth, float platformSpeed);
        Collisions(){};
        void update(Jack& player, sf::Texture* deathTexture, PlatformController& platforms, sf::Texture* originalColour, sf::Texture* newColour, Tent& tent, Score& score, GameSounds& gameSounds);

    private:
        float platformWidth;
        float platformSpeed;
};

#endif // COLLISIONS_H
