#include "Platform.h"
#include <SFML/Graphics.hpp>

Platform::Platform(sf::Texture* texture, float speed, bool movingRight, unsigned int gameRow)
{
    if(gameRow < 2 || gameRow > 5)
        throw "Trying to spawn platform out of bounds";
    this->speed = speed;
    this->movingRight = movingRight;
    this->gameRow = gameRow;
    velocity.y = 0.0f;
    platform.setTexture(*texture);
    platform.scale(height/platform.getLocalBounds().width, height/platform.getLocalBounds().height);
    platform.setOrigin(platform.getLocalBounds().width/2.0f, platform.getLocalBounds().top); //So the platform will spawn at the bottom of the game row.
    if(movingRight)
        platform.setPosition(0.0f+platform.getGlobalBounds().width/2.0f, (gameRow*180.0f)+90.0f);
    else
        platform.setPosition(1920.0f-platform.getGlobalBounds().width/2.0f, (gameRow*180.0f)+90.0f);
}

void Platform::changeDirection()
{
    movingRight = !movingRight;
}

void Platform::changeColour(sf::Texture* texture)
{
    platform.setTexture(*texture);
}

float Platform::width()
{
    return platform.getGlobalBounds().width;
}

void Platform::setPositionX(float x)
{
    platform.setPosition(x, platform.getPosition().y);
}

float Platform::getPositionX()
{
    return platform.getPosition().x;
}

void Platform::update(float deltaTime)
{
    velocity.x = 0.0f;

    if(movingRight)
        velocity.x += speed;
    else
        velocity.x -= speed;

    platform.move(velocity * deltaTime);
}

void Platform::draw(sf::RenderWindow& window)
{
    window.draw(platform);
}
