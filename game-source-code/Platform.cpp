#include "Platform.h"
#include <SFML/Graphics.hpp>

/*Platform::Platform(const float gameWidth, const float gameHeight)
{
    //Playing field image
    if(!platform.loadFromFile("resources/log.png"))
        throw "cannot load playing field image";
    platformImage.setTexture(platform);
    platformImage.setScale(gameWidth/platformImage.getLocalBounds().width, gameHeight/platformImage.getLocalBounds().height);
    sf::FloatRect platformRect = platformImage.getLocalBounds();
    platformImage.setOrigin(platformRect.left + platformRect.width/2.0f, platformRect.top + platformRect.height/2.0f);
    platformImage.setPosition(gameWidth/2.0f, gameHeight/1.7f);
}*/

Platform::Platform(sf::Texture* texture, float speed, bool movingRight, unsigned int gameRow)
{
    if(gameRow < 1 || gameRow > 5)
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

float Platform::width()
{
    return platform.getGlobalBounds().width;
}

void Platform::update(float deltaTime)
{
    velocity.x = 0.0f;

    if(movingRight)
        velocity.x += speed;
    else
        velocity.x -= speed;

    if(platform.getPosition().x - (platform.getGlobalBounds().width/2.0f) <= 0.0f && velocity.x < 0.0f)
        changeDirection();
    if(platform.getPosition().x + (platform.getGlobalBounds().width/2.0f) >= 1920 && velocity.x > 0.0f)
        changeDirection();

    platform.move(velocity * deltaTime);
}

void Platform::draw(sf::RenderWindow& window)
{
    window.draw(platform);
}
