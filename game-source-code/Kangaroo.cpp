#include "Kangaroo.h"
#include <vector>
#include "GameMode.h"

using namespace std;

Kangaroo::Kangaroo(sf::Texture* spritesheet, sf::Vector2u frameCount, float switchTime, float speed):
    animation{spritesheet, frameCount, switchTime}
{
    height = 100.0f;
    frameRow = 0;
    this->speed = speed;
    joey.setTexture(*spritesheet);
    joey.setPosition(0.51*1920.0f, 270); //assuming origin is the centre of the kangaroo
    joey.scale(height*frameCount.x/joey.getGlobalBounds().width, height*frameCount.y/joey.getGlobalBounds().height);
    velocity.x = 0;
    velocity.y = 0;
    movingRight = false;
}

Kangaroo::Kangaroo():
    animation{}
{}

void Kangaroo::update(vector<Jack>& players, float deltaTime, GameMode gameMode)
{
    if(gameMode == GameMode::Twoplayer)
    {
        if(players.at(0).row() == 1 || players.at(1).row() == 1) //tracks player if in the safe zone with joey
        {
            if(players.at(0).row() == 1 && players.at(1).row() == 1)
            {
                if(abs(players.at(0).getPositionX() - this->getPositionX()) <= abs(players.at(1).getPositionX() - this->getPositionX()))
                {
                    if(players.at(0).getPositionX() - this->getPositionX() > 0)
                    {
                        velocity.x = speed*deltaTime;
                        movingRight = true;
                    }
                    else
                    {
                        velocity.x = -speed*deltaTime;
                        movingRight = false;
                    }
                }
                else
                {
                    if(players.at(1).getPositionX() - this->getPositionX() > 0)
                    {
                        velocity.x = speed*deltaTime;
                        movingRight = true;
                    }
                    else
                    {
                        velocity.x = -speed*deltaTime;
                        movingRight = false;
                    }
                }
            }
            else if(players.at(0).row() != 1)
            {
                if(players.at(1).getPositionX() - this->getPositionX() > 0)
                {
                    velocity.x = speed*deltaTime;
                    movingRight = true;
                }
                else
                {
                    velocity.x = -speed*deltaTime;
                    movingRight = false;
                }
            }
            else
            {
                if(players.at(0).getPositionX() - this->getPositionX() > 0)
                {
                    velocity.x = speed*deltaTime;
                    movingRight = true;
                }
                else
                {
                    velocity.x = -speed*deltaTime;
                    movingRight = false;
                }
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
    }
    else //Code for singleplayer
    {
        if(players.at(0).row() == 1)
        {
            if(players.at(0).getPositionX() - this->getPositionX() > 0)
            {
                velocity.x = speed*deltaTime;
                movingRight = true;
            }
            else
            {
                velocity.x = -speed*deltaTime;
                movingRight = false;
            }
        }
        else
        {
            if(joey.getPosition().x <= 0.0f || joey.getPosition().x >= 1920.0f)
                movingRight = !movingRight;

            if(movingRight)
                velocity.x = speed*deltaTime;
            else
                velocity.x = -speed*deltaTime;
        }
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
