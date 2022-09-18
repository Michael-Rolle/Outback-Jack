#include "Jack.h"
#include <SFML/Graphics.hpp>

Jack::Jack(sf::Texture* texture, sf::Vector2u frameCount, float switchTime, float speed):
    animation(texture, frameCount, switchTime)
{
    this->speed = speed;
    row = 0; //idle animation
    facingRight = true;

    jack.setTexture(*texture);
    jack.scale(400.0f/jack.getLocalBounds().width, 400.0f/jack.getLocalBounds().height);
    jack.setPosition(960.0f, 320.0f);
}

void Jack::update(float deltaTime)
{
    sf::Vector2f movement(0.0f, 0.0f);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        movement.x -= speed * deltaTime;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        movement.x += speed * deltaTime;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        movement.y -= speed * deltaTime;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        movement.y += speed * deltaTime;

    if(movement.x == 0.0f && movement.y == 0.0f)
    {
        row = 0; //idle animation
    }
    else
    {
        row = 1; //walking animation

        if(movement.x == 0)
            facingRight = facingRight;
        else if(movement.x > 0.0f)
            facingRight = true;
        else
            facingRight= false;
    }

    if(jack.getPosition().x - (400/2 - padding.x) <= 0.0f && movement.x < 0.0f)
        movement.x = 0;
    if(jack.getPosition().x + (400/2 - padding.x) >= 1920 && movement.x > 0.0f)
        movement.x = 0;
    if(jack.getPosition().y - (400/2 - padding.y) <= 0.0f && movement.y < 0.0f)
        movement.y = 0;
    if(jack.getPosition().y + (400/2 - padding.y) >= 1080 && movement.y > 0.0f)
        movement.y = 0;

    animation.update(row, deltaTime, facingRight);
    jack.setTextureRect(animation.textRect);
    jack.move(movement);
}

void Jack::draw(sf::RenderWindow& window)
{
    window.draw(jack);
}
