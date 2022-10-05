#include "Enemy.h"
#include <SFML/Graphics.hpp>

Enemy::Enemy(sf::Texture* texture, float speed, bool movingRight, unsigned int gameRow)
{
    if(gameRow < 2 || gameRow > 5)
        throw "Trying to spawn enemy out of bounds";
    this->speed = speed;
    this->movingRight = movingRight;
    this->gameRow = gameRow;
    velocity.y = 0.0f;
    enemy.setTexture(*texture);
    enemy.scale(height/enemy.getLocalBounds().width, height/enemy.getLocalBounds().height);
    enemy.setOrigin(enemy.getLocalBounds().width/2.0f, enemy.getLocalBounds().top); //So the enemy will spawn at the bottom of the game row.
    if(movingRight)
        enemy.setPosition(0.0f+enemy.getGlobalBounds().width/2.0f, (gameRow*180.0f)-5.0f);
    else
        enemy.setPosition(1920.0f-enemy.getGlobalBounds().width/2.0f, (gameRow*180.0f)-5.0f);
}

float Enemy::width()
{
    return enemy.getGlobalBounds().width;
}

void Enemy::setPositionX(float x)
{
    enemy.setPosition(x, enemy.getPosition().y);
}

float Enemy::getPositionX()
{
    return enemy.getPosition().x;
}

void Enemy::update(float deltaTime)
{
    velocity.x = 0.0f;
    sf::IntRect textRect;
    textRect.top = enemy.getLocalBounds().top;
    textRect.height = enemy.getLocalBounds().height;

    if(movingRight)
    {
        velocity.x += speed;
        textRect.left = enemy.getLocalBounds().left + enemy.getLocalBounds().width;
        textRect.width = -enemy.getLocalBounds().width;
    }

    if(!movingRight)
    {
        velocity.x -= speed;
        textRect.left = enemy.getLocalBounds().left;
        textRect.width = enemy.getLocalBounds().width;
    }

    enemy.setTextureRect(textRect);
    enemy.move(velocity * deltaTime);
}

void Enemy::draw(sf::RenderWindow& window)
{
    window.draw(enemy);
}
