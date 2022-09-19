#ifndef PLATFORM_H
#define PLATFORM_H
#include "Jack.h"
#include <SFML/Graphics.hpp>


class Platform
{
    public:
        Platform(const float gameWidth, const float gameHeight);
        isActive(Jack jack);
        void renderPlatform(sf::RenderWindow& window);

        bool active;
        sf::Texture platform;
        sf::Sprite platformImage;
};

#endif
