#include "Jack.h"
#include <SFML/Graphics.hpp>

Jack::Jack(sf::Texture* texture, sf::Vector2u frameCount, float switchTime, float speed):
    animation(texture, frameCount, switchTime)
{
    this->speed = speed; //pixels per second
    frameRow = 0; //idle animation
    facingRight = true;
    gameRow = 1; //safe zone
    isJumping = false;
    jumpingUp = false;

    const auto jackHeight = 100.0f; //How many pixels tall Jack is
    jack.setTexture(*texture);
    jack.scale(jackHeight*frameCount.y/jack.getLocalBounds().width, jackHeight*frameCount.y/jack.getLocalBounds().height);
    jack.setPosition(960.0f, 180.0f + 90.0f);
}

void Jack::update(float deltaTime)
{
    sf::Vector2f movement(0.0f, 0.0f);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        movement.x -= speed * deltaTime;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        movement.x += speed * deltaTime;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !isJumping && gameRow != 1)
    {
        isJumping = true;
        jumpingUp = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !isJumping && gameRow != 6)
    {
        isJumping = true;
        jumpingUp = false;
    }

    if(isJumping)
    {
        frameRow = 2; //jumping animation
        movement.y += jumpingSpeed(jumpingUp)*deltaTime;
    }
    else if(movement.x == 0.0f && movement.y == 0.0f)
        frameRow = 0; //idle animation
    else
    {
        frameRow = 1; //walking animation

        if(movement.x > 0.0f)
            facingRight = true;
        else if(movement.x < 0.0f)
            facingRight= false;
    }

    if(jack.getPosition().x - (jack.getGlobalBounds().width/2.0f) <= 0.0f && movement.x < 0.0f)
        movement.x = 0;
    if(jack.getPosition().x + (jack.getGlobalBounds().width/2.0f) >= 1920 && movement.x > 0.0f)
        movement.x = 0;

    animation.update(frameRow, deltaTime, facingRight);
    jack.setTextureRect(animation.textRect);
    jack.setOrigin(jack.getLocalBounds().width/2.0f, jack.getLocalBounds().height/2.0f);
    jack.move(movement);
}

float Jack::jumpingSpeed(bool up)
{
    if(up)
    {
        if(jack.getPosition().y <= (gameRow*180)-90)
        {
            isJumping = false;
            gameRow--;
        }
        return -300.0f; //therefore it will take 180/300 = 0.6 seconds to do a full jump (time per animation frame is 0.2s)
    }
    else
    {
        if(jack.getPosition().y >= (gameRow*180)+90)
        {
            isJumping = false;
            gameRow++;
        }
        return 360.0f;
    }
}

void Jack::draw(sf::RenderWindow& window)
{
    window.draw(jack);
}
