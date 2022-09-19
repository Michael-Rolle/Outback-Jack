#include "platform.h"
#include <SFML/Graphics.hpp>

Platform::Platform(const float gameWidth, const float gameHeight)
{
    //Playing field image
    if(!platform.loadFromFile("resources/basic_platform.png"))
        throw "cannot load playing field image";
    platformImage.setTexture(platform);
    platformImage.setScale(gameWidth/platformImage.getLocalBounds().width, gameHeight/platformImage.getLocalBounds().height);
    sf::FloatRect platformRect = platformImage.getLocalBounds();
    platformImage.setOrigin(platformRect.left + platformRect.width/2.0f, platformRect.top + platformRect.height/2.0f);
    platformImage.setPosition(gameWidth/2.0f, gameHeight/1.7f);
}

Platform::isActive(Jack jack)
{

}

void Platform::renderPlatform(sf::RenderWindow& window)
{
    window.draw(platformImage);
}
