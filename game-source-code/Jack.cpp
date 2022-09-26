#include "Jack.h"
#include <SFML/Graphics.hpp>
#include <cmath>

Jack::Jack(sf::Texture* texture, sf::Vector2u frameCount, float switchTime, float speed):
    animation(texture, frameCount, switchTime)
{
    this->speed = speed; //pixels per second
    frameRow = 0; //idle animation
    facingRight = true;
    gameRow = 1; //safe zone
    isJumping = false;
    canJump = true;
    movingLeft = false;
    movingRight = false;
    jumpHeight = 180.0f; //1/6 of the gameHeight
    velocity.x = 0;
    velocity.y = 0;

    const auto jackHeight = 100.0f; //How many pixels tall Jack is
    jack.setTexture(*texture);
    jack.scale(jackHeight*frameCount.y/jack.getLocalBounds().width, jackHeight*frameCount.y/jack.getLocalBounds().height);
    jack.setPosition(960.0f, 180.0f + 90.0f);
}

Jack::Jack(const Jack& player):
    animation(player.animation)
{
    this->canJump = player.canJump;
    this->facingRight = player.facingRight;
    this->gameRow = player.gameRow;
    this->jack = player.jack;
    this->frameRow = player.frameRow;
    this->jumpHeight = player.jumpHeight;
    this->jumpingUp = player.jumpingUp;
    this->movingLeft = player.movingLeft;
    this->movingRight = player.movingRight;
    this->speed = player.speed;
    this->velocity = player.velocity;
}

Jack& Jack::operator= (const Jack& player)
{
    auto jack = Jack{player};
    return jack;
}

void Jack::update(float deltaTime)
{
    if(movingLeft)
        velocity.x -= speed;
    if(movingRight)
        velocity.x += speed;

    if(isJumping)
    {
        frameRow = 2; //jumping animation
        jump();
        velocity.y += 981.0f * deltaTime;
    }
    else if(!movingRight && !movingLeft)
        frameRow = 0; //idle animation
    else
        frameRow = 1; //walking animation

    if(movingRight)
        facingRight = true;
    else if(movingLeft)
        facingRight= false;

    if(!isJumping)
        velocity.y = 0;

    if(jack.getPosition().x - (jack.getGlobalBounds().width/2.0f) <= 0.0f && velocity.x < 0.0f)
        velocity.x = 0;
    if(jack.getPosition().x + (jack.getGlobalBounds().width/2.0f) >= 1920 && velocity.x > 0.0f)
        velocity.x = 0;

    animation.update(frameRow, deltaTime, facingRight);
    jack.setTextureRect(animation.textRect);
    jack.setOrigin(jack.getLocalBounds().width/2.0f, jack.getLocalBounds().height/2.0f);
    jack.move(velocity * deltaTime);
    velocity.x = 0.0f;
}

void Jack::setMovement(sf::Event event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::D)
            movingRight = true;
        if(event.key.code == sf::Keyboard::A)
            movingLeft = true;
        if(event.key.code == sf::Keyboard::W && !isJumping && gameRow != 1 && canJump)
        {
            isJumping = true;
            jumpingUp = true;
            canJump = false;
        }
        if(event.key.code == sf::Keyboard::S && !isJumping && gameRow != 5 && canJump)
        {
            isJumping = true;
            jumpingUp = false;
            canJump = false;
        }
    }
    else if(event.type == sf::Event::KeyReleased)
    {
        if(event.key.code == sf::Keyboard::A)
            movingLeft = false;
        if(event.key.code == sf::Keyboard::D)
            movingRight = false;
        if(event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::S)
            canJump = true;
    }
}

void Jack::addVelocityX(float speed, bool right)
{
    if(right)
        velocity.x = speed;
    else
        velocity.x = -speed;
}

void Jack::jump()
{
    if(jumpingUp)
    {
        if(velocity.y > 0 && jack.getPosition().y >= (gameRow*180)-90)
        {
            isJumping = false;
            gameRow--;
            velocity.y = 0.0f;
            return;
        }
        if(velocity.y == 0)
            velocity.y = -sqrtf(2.0f * 981.0f * 190.0f); //Initial velocity using kinematic equations
    }
    else
    {
        if(jack.getPosition().y >= ((gameRow+1)*180)+90)
        {
            isJumping = false;
            gameRow++;
            velocity.y = 0.0f;
            return;
        }
        if(velocity.y == 0)
            velocity.y = -sqrtf(2.0f * 981.0f * 10.0f); //Initial velocity using kinematic equations
    }
}

void Jack::draw(sf::RenderWindow& window)
{
    window.draw(jack);
}
