#ifndef JACK_H
#define JACK_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"
#include "Tent.h"

class Jack
{
    public:
        Jack(sf::Texture* texture, sf::Vector2u frameCount, float switchTime, float speed);
        void setMovement(sf::Event event);
        void addVelocityX(float speed, bool right);
        void update(float deltaTime);
        void draw(sf::RenderWindow& window);
        void die(sf::Texture* texture);
        bool jumping(){ return isJumping; }
        float getPositionX() { return jack.getPosition().x; }
        float width() { return jack.getGlobalBounds().width; }
        unsigned int row() { return gameRow; }
        bool wonGame(sf::Event event, Tent& tent);
    private:
        void jump(); //sets the vertical velocity

    public:
        bool isAlive;
        bool playJumpSound;
        bool playLandingSound;
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
