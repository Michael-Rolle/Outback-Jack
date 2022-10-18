#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>

/*! Creates an Enemy object in a specified row. The Enemy can move. */

class Enemy
{
    public:
        Enemy(sf::Texture* texture, float speed, bool movingRight, unsigned int gameRow);
        ~Enemy(){}
        void setPositionX(float x); /*!< Sets the x coordinate of the enemy depending on the input float.
                                         Parameters do not allow the setting of the y coordinate of the enemy. */
        float getPositionX(); /*!< Returns the x coordinate of the enemy as a float for use in other member functions. */
        void update(float deltaTime); /*!< Moves the enemy along the x axis, while facing the correct direction, as the
                                           game time increases. Takes in a float tracking the game time to update the
                                           enemies position. */
        void draw(sf::RenderWindow& window); /*!< Draws the enemy onto the screen. Takes in a reference to a RenderWindow
                                                  to be able to use the draw function. */
        float width(); /*!< Returns the width value of the global bounds of the enemy as a float for use in other member
                            functions. */

    private:
        sf::Sprite enemy;
        bool movingRight;
        bool facingRight;
        unsigned int gameRow;
        float speed;
        sf::Vector2f velocity;
        const float height = 90;
};

#endif
