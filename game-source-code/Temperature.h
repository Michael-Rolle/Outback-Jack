#ifndef TEMPERATURE_H
#define TEMPERATURE_H
#include <SFML/Graphics.hpp>

class Temperature
{
    public:
        Temperature(const float gameWidth, const float gameHeight);
        void renderTemperature(sf::RenderWindow& window);
        void update(sf::RenderWindow& window, float deltaTime);

    private:
        sf::Font font;
        sf::Text temperature;
        sf::Text degrees;
        float totalTime;
};

#endif
