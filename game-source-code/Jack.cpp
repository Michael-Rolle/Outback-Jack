#include "Jack.h"
#include <SFML/Graphics.hpp>

/*Jack::Jack(const sf::Texture* jack_spritesheet, const float gameWidth, const float gameHeight, sf::RenderWindow& window)
{
    //Texture
    //if(!jack_spritesheet.loadFromFile("resources/jack_spritesheet.png"))
    //    throw "cannot load texture file";
    //this->jack_spritesheet = jack_spritesheet;
    jack.setTexture(*jack_spritesheet);
    jack.setTextureRect(sf::IntRect(256, 0, 256, 256));
    jackRect = jack.getLocalBounds();
    jack.setOrigin(jackRect.left + jackRect.width/2, jackRect.top + jackRect.height/2);
    jack.setPosition(window.getView().getCenter().x, window.getView().getCenter().y - 0.75*(gameHeight/2));
    jack.setScale(0.1*(gameHeight/jackRect.height), 0.1*(gameHeight/jackRect.height));
}*/

Jack::Jack(sf::Texture* texture, sf::Vector2u frameCount, float switchTime, float speed):
    animation(texture, frameCount, switchTime)
{
    this->speed = speed;
    row = 0; //idle animation is at row 0
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

    if(jack.getPosition().x - (400/2) <= 0.0f && movement.x < 0.0f)
        movement.x = 0;
    if(jack.getPosition().x + (400/2) >= 1920 && movement.x > 0.0f)
        movement.x = 0;
    if(jack.getPosition().y - (400/2) <= 0.0f && movement.y < 0.0f)
        movement.y = 0;
    if(jack.getPosition().y + (400/2) >= 1080 && movement.y > 0.0f)
        movement.y = 0;

    animation.update(row, deltaTime, facingRight);
    jack.setTextureRect(animation.textRect);
    jack.move(movement);
}

void Jack::draw(sf::RenderWindow& window)
{
    window.draw(jack);
}

/*

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

void Jack::playWalkAnimation(sf::Clock& clock)
{
    if(clock.getElapsedTime().asSeconds() > 0.2f)
    {
        if(textureRect.left==512)
            textureRect.left = 0;
        else
            textureRect.left += 256;

        jack.setTextureRect(textureRect);
        clock.restart();
    }
}

void Jack::moveJack(const float playerSpeed, const float deltaTime, const float gameWidth, const float gameHeight, sf::Clock& clock)
{
    auto x = getJackPositionX();
    auto y = getJackPositionY();

    //Movement
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && x + ((jackRect.width/2)-padding.x) < gameWidth)
    {
        jack.move(playerSpeed*deltaTime, 0.f);
        jack.setTextureRect(sf::IntRect(jack.getTextureRect().left, 0, 256, 256));
        playWalkAnimation(clock);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && x - ((jackRect.width/2)-padding.x) > 0.f)
    {
        jack.move(-playerSpeed*deltaTime, 0.f);
        jack.setTextureRect(sf::IntRect(jack.getTextureRect().left, 256, 256, 256));
        playWalkAnimation(clock);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && y - ((jackRect.height/2)-padding.y) > 0.f)
    {
        jack.move(0.f, -playerSpeed*deltaTime);
        //jack.setTextureRect(sf::IntRect(jack.getTextureRect().left, jack.getTextureRect().top, 256, 256));
        playWalkAnimation(clock);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && y + ((jackRect.height/2)-padding.y) < gameHeight)
    {
        jack.move(0.f, playerSpeed*deltaTime);
        //jack.setTextureRect(sf::IntRect(jack.getTextureRect().left, jack.getTextureRect().top, 256, 256));
        playWalkAnimation(clock);
    }
    //else
        //jack.setTextureRect(sf::IntRect(256, jack.getTextureRect().top, 256, 256));


}

void Jack::setTextureRect(sf::IntRect rect)
{
    jack.setTextureRect(rect);
    textureRect = rect;
}

sf::IntRect Jack::getTextureRect()
{
    return textureRect;
}

void Jack::renderJack(sf::RenderWindow& window)
{
    window.draw(jack);
}*/
