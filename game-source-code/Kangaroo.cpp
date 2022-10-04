#include "Kangaroo.h"

Kangaroo::Kangaroo(sf::Texture* spritesheet, sf::Vector2u frameCount, float switchTime, float speed):
    animation{spritesheet, frameCount, switchTime}
{
    height = 150.0f;
    frameRow = 0;
    this->speed = speed;
    joey.setTexture(*spritesheet);
    joey.setPosition(1800, 270); //assuming origin is the centre of the kangaroo
    joey.scale(height*frameCount.y/joey.getLocalBounds().width, height*frameCount.y/joey.getLocalBounds().height);
    velocity.x = 0;
    velocity.y = 0;
    movingRight = false;
}

Kangaroo::Kangaroo():
    animation{}
{}

void Kangaroo::update(Jack& player, float deltaTime)
{
    if(player.row() == 1) //tracks player if in the safe zone with joey
    {
        if(player.getPositionX() <= joey.getPosition().x)
        {
            velocity.x = -speed*deltaTime;
            movingRight = false;
        }
        else if(player.getPositionX() >= joey.getPosition().x)
        {
            velocity.x = speed*deltaTime;
            movingRight = true;
        }
    }
    else //wanders from side to side
    {
        if(joey.getPosition().x <= 0.0f || joey.getPosition().x >= 1920.0f)
            movingRight = !movingRight;

        if(movingRight)
            velocity.x = speed*deltaTime;
        else
            velocity.x = -speed*deltaTime;
    }

    animation.update(frameRow, deltaTime, movingRight);
    joey.setTextureRect(animation.textRect);
    joey.setOrigin(joey.getLocalBounds().width/2.0f, joey.getLocalBounds().height/2.0f);
    joey.move(velocity);
}

void Kangaroo::draw(sf::RenderWindow& window)
{
    window.draw(joey);
}
