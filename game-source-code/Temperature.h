#ifndef TEMPERATURE_H
#define TEMPERATURE_H
#include <SFML/Graphics.hpp>
#include "Jack.h"

/*!
Displays and increases the temperature of the playing field. Once the temperature reaches 50 degrees, the player dies.
*/

class Temperature
{
    public:
        Temperature(const float gameWidth, const float gameHeight);
        void draw(sf::RenderWindow& window);
        /*!< Draws the current value of the temperature with reference to a RenderWindow. */
        void update(Jack& player, sf::Texture* deathTexture, float deltaTime);
        /*!< Increments the temperature with the float value. If the temperature reaches 50 degrees, the player dies and their current texture is replaced with the Texture parameter. */
        void reset();
        /*!< Resets the temperature to zero degrees. */

    public:
        float temp;
        sf::Text temperature;
    private:
        sf::Font font;
        sf::Text degrees;
};

#endif
