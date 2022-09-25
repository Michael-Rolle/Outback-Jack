#include "platform.h"
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

Platform::Platform(sf::Texture* texture, float speed, bool movingRight, bool gameRow)
{
    this->speed = speed;
    this->movingRight = movingRight;
    this->gameRow = gameRow;
    platform.setTexture(*texture);
    platform.scale(height/platform.getLocalBounds().width, height/platform.getLocalBounds().height);
    platform.setOrigin(platform.getLocalBounds().width/2, platform.getLocalBounds().top); //So the platform will spawn at the bottom of the game row.
    if(movingRight)
        platform.setPosition(0+platform.getGlobalBounds()/2, (gameRow*180)+90);
    else
        platform.setPosition(1080-platform.getGlobalBounds()/2, (gameRow*180)+90);
}

void Platform::changeDirection()
{
    movingRight = !movingRight;
}

void Platform::update(float deltaTime)
{

}

void Platform::draw(sf::RenderWindow& window)
{
    window.draw(platformImage);
}
