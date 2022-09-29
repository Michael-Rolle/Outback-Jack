#ifndef COLLISIONS_H
#define COLLISIONS_H
#include <SFML/Graphics.hpp>
#include "PlatformController.h"
#include "Jack.h"

class Collisions
{
    public:
        Collisions(float platformWidth, float platformSpeed);
        void update(Jack& player, sf::Texture* deathTexture, PlatformController& platforms, sf::Texture* originalColour, sf::Texture* newColour);

    private:
        float platformWidth;
        float platformSpeed;
};

#endif // COLLISIONS_H
