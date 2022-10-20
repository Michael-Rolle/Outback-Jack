#ifndef PLATFORM_H
#define PLATFORM_H
#include <SFML/Graphics.hpp>

/*!
Creates a Platform object capable of horizontal movement, being able to change colour and being able to change direction when the player presses the shift key.
*/

class Platform
{
    public:
        Platform(sf::Texture* texture, float speed, bool movingRight, unsigned int gameRow);
        ~Platform(){}
        void changeDirection();
        /*!< Reverses the Platform objects' current direction. */
        void changeColour(sf::Texture* texture);
        /*!< Changes the Platform objects' current texture to the texture specified in the parameter. */
        void setPositionX(float x);
        /*!< Sets the Platform objects' horizontal position to that specified by the float parameter, without changing its vertical position. */
        float getPositionX();
        /*!< Returns the horizontal position of the Platform object as a float. */
        void update(float deltaTime);
        /*!< Updates the Platform object to move at a constant speed, either left or right. */
        void draw(sf::RenderWindow& window);
        /*!< Draws the Platform object with referencce to a RenderWindow. */
        float width();
        /*!< Returns the global width of the Platform object as a float. */

    private:
        sf::Sprite platform;
        bool movingRight;
        unsigned int gameRow;
        float speed;
        sf::Vector2f velocity;
        const float height = 90;
};

#endif
