#include "Jack.h"
#include <SFML/Graphics.hpp>

Jack::Jack(const float gameWidth, const float gameHeight, sf::RenderWindow& window)
{
    //Texture
    if(!jack_standing.loadFromFile("resources/jack.png"))
        throw "cannot load texture file";

    jack.setTexture(jack_standing);
    jackRect = jack.getLocalBounds();
    jack.setOrigin(jackRect.left + jackRect.width/2, jackRect.top + jackRect.height/2);
    jack.setPosition(window.getView().getCenter().x, window.getView().getCenter().y - 0.75*(gameHeight/2));
    jack.setScale(0.1*(gameHeight/jackRect.height), 0.1*(gameHeight/jackRect.height));
}

sf::FloatRect Jack::getJackLocalBounds()
{
    return jackRect;
}

float Jack::getJackPositionX()
{
    return jack.getPosition().x;
}

float Jack::getJackPositionY()
{
    return jack.getPosition().y;
}

void Jack::moveJack(float playerSpeed, float deltaTime, char D)
{
    switch(D)
    {
    case 'D':
        jack.move(playerSpeed*deltaTime, 0.f);
        break;
    case 'A':
        jack.move(-playerSpeed*deltaTime, 0.f);
        break;
    case 'W':
        jack.move(0.f, -playerSpeed*deltaTime);
        break;
    case 'S':
        jack.move(0.f, playerSpeed*deltaTime);
        break;
    }

}

void Jack::renderJack(sf::RenderWindow& window)
{
    window.draw(jack);
}
