#ifndef TENT_H
#define TENT_H
#include <SFML/Graphics.hpp>

/*!
Visually and incremementally, constructs/deconstructs a tent using member functions. The tent cannot be deconstructed if none of it has been built and stops being being constructed if it is already
fully built.
*/

class Tent
{
    public:
        Tent(sf::Texture* texture, unsigned int rows, unsigned int columns, float height);
        Tent(){};
        void nextFrame();
        /*!< Adds the next frame to the tent if it is not fully built. Frames are added horizontally and then vertically. */
        void removeFrame();
        /*!< Removes the most recent frame from the tent while it is not fully deconstructed. */
        float getPositionX();
        /*!< Returns the horizontal position of the tents' sprite as a float. */
        float width();
        /*!< Returns the global width of the tents' sprite as a float. */
        void draw(sf::RenderWindow& window); /*!< Draws the current state of the tent including all constructed frames. */
        void reset();
        /*!< Fully deconstructs the tent by resetting its frames. */

    public:
        bool built;
    private:
        sf::Sprite tent;
        sf::Vector2u numFrames;
        sf::Vector2u currentFrame;
        sf::IntRect textRect;
        float height;
};

#endif // TENT_H
