#ifndef KANGAROO_H
#define KANGAROO_H
#include <SFML/Graphics.hpp>
#include "Jack.h"
#include "Animation.h"

/*!
Creates a Kangaroo enemy capable of killing the player. The Kangaroo can move left or right within the safe zone and tracks
the player if they are in the safe zone.
*/

class Kangaroo
{
    public:
        Kangaroo(sf::Texture* spritesheet, sf::Vector2u frameCount, float switchTime, float speed);
        Kangaroo();
        float getPositionX(){ return joey.getPosition().x; } /*!< Returns the horizontal position of the Kangaroo as a float. */
        float width(){ return joey.getGlobalBounds().width; } /*!< Returns the width of the Kangaroo as a float. */
        void update(Jack& player, float deltaTime); /*!< Updates the Kangaroo object to wander if the player is outside the
                                                         safe zone, or to track the player if they are within the safe zone.
                                                         Tracks the player by taking a in reference to them to read their x
                                                         position. Updates the Kangaroo objects postion by taking in a float.*/
        void draw(sf::RenderWindow& window); /*!< Draws the Kangaroo object with reference to a RenderWindow. */

    private:
        Animation animation;
        sf::Sprite joey;
        float height;
        float speed;
        bool movingRight;
        unsigned int frameRow;
        sf::Vector2f velocity;
};

#endif // KANGAROO_H
