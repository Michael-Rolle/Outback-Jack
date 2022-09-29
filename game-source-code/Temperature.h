#ifndef TEMPERATURE_H
#define TEMPERATURE_H
#include <SFML/Graphics.hpp>
#include "Jack.h"

class Temperature
{
    public:
        Temperature(const float gameWidth, const float gameHeight);
        void draw(sf::RenderWindow& window);
        void update(Jack& player, sf::Texture* deathTexture, float deltaTime);

    private:
        sf::Font font;
        sf::Text temperature;
        sf::Text degrees;
        float totalTime;
};

#endif
