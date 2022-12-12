#include "Jack.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include "PlayerNumber.h"

Jack::Jack(sf::Texture* texture, sf::Vector2u frameCount, float switchTime, float speed, int playerNum):
    animation(texture, frameCount, switchTime)
{
    this->speed = speed; //pixels per second
    this->playerNum = playerNum;
    frameRow = 0; //idle animation
    victory = false;
    if(playerNum == 1)
        facingRight = true;
    else
        facingRight = false;
    isAlive = true;
    gameRow = 1; //safe zone
    isJumping = false;
    canJump = true;
    movingLeft = false;
    movingRight = false;
    jumpHeight = 180.0f; //1/6 of the gameHeight
    velocity.x = 0;
    velocity.y = 0;
    height = 100.0f;
    score = 0.0f;

    jack.setTexture(*texture);
    jack.scale(height*frameCount.y/jack.getLocalBounds().width, height*frameCount.y/jack.getLocalBounds().height);
    if(playerNum == 1)
        jack.setPosition(0.25*1920.0f, 180.0f + 90.0f);
    else if(playerNum == 2)
        jack.setPosition(0.75*1920.0f, 180.0f + 90.0f);
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
        velocity.y += 1500.0f * deltaTime;
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

    if(gameRow == 1)
    {
        if((jack.getPosition().x + jack.getGlobalBounds().width/2.0f >= 1920 && movingRight) || (jack.getPosition().x - jack.getGlobalBounds().width/2.0f <= 0 && movingLeft))
            velocity.x = 0.0f;
    }

    animation.update(frameRow, deltaTime, facingRight);
    jack.setTextureRect(animation.textRect);
    jack.setOrigin(jack.getLocalBounds().width/2.0f, jack.getLocalBounds().height/2.0f);
    jack.move(velocity * deltaTime);
    velocity.x = 0.0f;
}

void Jack::setMovement(sf::Event event, GameSounds& gameSounds)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(this->playerNum == 1)
        {
            if(event.key.code == sf::Keyboard::D)
                movingRight = true;
            if(event.key.code == sf::Keyboard::A)
                movingLeft = true;
            if(event.key.code == sf::Keyboard::W && !isJumping && gameRow != 1 && canJump)
            {
                gameSounds.playJumpSound();
                isJumping = true;
                jumpingUp = true;
                canJump = false;
                return;
            }
            if(event.key.code == sf::Keyboard::S && !isJumping && gameRow != 5 && canJump)
            {
                gameSounds.playJumpSound();
                isJumping = true;
                jumpingUp = false;
                canJump = false;
                return;
            }
        }
        else if(this->playerNum == 2)
        {
            if(event.key.code == sf::Keyboard::Right)
                movingRight = true;
            if(event.key.code == sf::Keyboard::Left)
                movingLeft = true;
            if(event.key.code == sf::Keyboard::Up && !isJumping && gameRow != 1 && canJump)
            {
                gameSounds.playJumpSound();
                isJumping = true;
                jumpingUp = true;
                canJump = false;
                return;
            }
            if(event.key.code == sf::Keyboard::Down && !isJumping && gameRow != 5 && canJump)
            {
                gameSounds.playJumpSound();
                isJumping = true;
                jumpingUp = false;
                canJump = false;
                return;
            }
        }
    }

    else if(event.type == sf::Event::KeyReleased)
    {
        if(this->playerNum == 1)
        {
            if(event.key.code == sf::Keyboard::A)
                movingLeft = false;
            if(event.key.code == sf::Keyboard::D)
                movingRight = false;
            if(event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::S)
                canJump = true;
        }
        else if(this->playerNum == 2)
        {
            if(event.key.code == sf::Keyboard::Left)
                movingLeft = false;
            if(event.key.code == sf::Keyboard::Right)
                movingRight = false;
            if(event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down)
                canJump = true;
        }
    }
}

void Jack::addVelocityX(float speed, bool right)
{
    if(right)
        velocity.x = speed;
    else
        velocity.x = -speed;
}

void Jack::die(sf::Texture* texture)
{
    isAlive = false;
    jack.setTexture(*texture);
    sf::IntRect textRect;
    textRect.top = jack.getLocalBounds().top;
    textRect.height = jack.getLocalBounds().height;
    if(facingRight)
    {
        textRect.left = jack.getLocalBounds().left;
        textRect.width = jack.getLocalBounds().width;
    }
    else //flips to face the other direction
    {
        textRect.left = jack.getLocalBounds().left + jack.getLocalBounds().width;
        textRect.width = -jack.getLocalBounds().width;
    }
    jack.setTextureRect(textRect);
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
            velocity.y = -sqrtf(2.0f * 1500.0f * 190.0f); //Initial velocity using kinematic equations
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
            velocity.y = -sqrtf(2.0f * 1500.0f * 10.0f); //Initial velocity using kinematic equations
    }
}

bool Jack::wonGame(sf::Event event, Tent& tent, PlayerNumber num)
{
    if(!tent.built)
        return false;
    if(event.type == sf::Event::KeyPressed)
    {
        if(num == PlayerNumber::One && (event.key.code == sf::Keyboard::W) && abs(jack.getPosition().x - tent.getPositionX()) <= tent.width()/2.0f && gameRow == 1)
        {
            victory = true;
            return true;
        }

        else if(num == PlayerNumber::Two && (event.key.code == sf::Keyboard::Up) && abs(jack.getPosition().x - tent.getPositionX()) <= tent.width()/2.0f && gameRow == 1)
        {
            victory = true;
            return true;
        }
    }
    return false;
}

void Jack::draw(sf::RenderWindow& window)
{
    window.draw(jack);
}
