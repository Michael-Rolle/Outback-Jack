#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>

/*!
Handles animations for each object equipped to handle an animation. Uses a 2D vector to select which texture to use at any point and then updates the object with the texture.
*/

class Animation
{
    public:
        Animation(sf::Texture* texture, sf::Vector2u frameCount, float switchTime);
        Animation(){}
        void update(int row, float deltaTime, bool facingRight);
        /*!< Updates an objects texture to animate it. Takes in an integer to specify the y coordinate in the 2d vector, a float to update the texture over time and hence specify the x
             coordinate in the 2d vector, and a bool to change the texture updating depending on the direction the object is facing. Parameters restrict object to only facing left or right. */
        sf::IntRect textRect;

    private:
        sf::Vector2u frameCount;
        sf::Vector2u currentFrame;
        float totalTime; //time since last changed frame
        float switchTime; //time between switching frames
};

#endif // ANIMATION_H
