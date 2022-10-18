#ifndef JACK_H
#define JACK_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameSounds.h"
#include "Animation.h"
#include "Tent.h"

/*!
Creates a player for the game. The player is capable of being moved around and jumping using keyboard inputs.
*/

class Jack
{
    public:
        Jack(sf::Texture* texture, sf::Vector2u frameCount, float switchTime, float speed);
        void setMovement(sf::Event event, GameSounds& gameSounds); /*!< Takes in an Event object to move the player respectively. */
        void addVelocityX(float speed, bool right); /*!< Adds horizontal velocity to the player by the value designated by
                                                         the float and in the direction specified by the bool.*/
        void update(float deltaTime); /*!< Updates the position and animation frame of the player respective to the float. */
        void draw(sf::RenderWindow& window); /*!< Draws the player with reference to a RenderWindow. */
        void die(sf::Texture* texture); /*!< Change the players texture to the parameter Texture if they die. */
        bool jumping(){ return isJumping; } /*!< Check if the player is currently jumping. */
        float getPositionX() { return jack.getPosition().x; } /*!< Returns the x coordinates of the player as a float. */
        float width() { return jack.getGlobalBounds().width; } /*!< Returns the global width of the players' sprite as a float. */
        unsigned int row() { return gameRow; } /*!< Returns the game row the player currently exists in. There are only six rows. */
        bool wonGame(sf::Event event, Tent& tent); /*!< Checks if the player has won the game. Takes in an Event object to check
                                                        the player has jumped to the safe zone and a reference to a Tent object
                                                        to check the player has moved to the Tent door.*/

    private:
        void jump(); //sets the vertical velocity

    public:
        bool isAlive;
        float score;
    private:
        sf::Sprite jack;
        Animation animation;
        unsigned int frameRow;
        unsigned int gameRow; //Board is divided into 6 rows, tells you what row Jack is on
        float speed;
        bool facingRight;
        bool canJump;
        bool isJumping;
        bool jumpingUp;
        bool movingRight;
        bool movingLeft;
        float jumpHeight;
        float height;
        sf::Vector2f velocity;
};

#endif
