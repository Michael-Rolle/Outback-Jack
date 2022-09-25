#ifndef JACK_H
#define JACK_H
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Jack
{
    public:
        Jack(sf::Texture* texture, sf::Vector2u frameCount, float switchTime, float speed);
        void setMovement(sf::Event event);
        void addVelocityX(float speed, bool right);
        void update(float deltaTime);
        void draw(sf::RenderWindow& window);
    private:
        void jump(); //sets the vertical velocity

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
        sf::Vector2f velocity;
};

#endif
