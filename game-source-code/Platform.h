#ifndef PLATFORM_H
#define PLATFORM_H
#include "Jack.h"
#include <SFML/Graphics.hpp>


class Platform
{
    public:
        Platform(sf::Texture* texture, float speed, bool movingRight);
        void changeDirection();
        void update(float deltaTime);
        void draw(sf::RenderWindow& window);
        //isActive(Jack jack);
        //void renderPlatform(sf::RenderWindow& window);

        //bool active;
        //sf::Texture platform;
        sf::Sprite platform;
        bool movingRight;
        unsigned int gameRow;
        float speed;
        sf::Vector2f velocity;
};

#endif
