#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>

class Enemy
{
    public:
        Enemy(sf::Texture* texture, float speed, bool movingRight, unsigned int gameRow);
        ~Enemy(){}
        void changeDirection();
        void setPositionX(float x);
        float getPositionX();
        void update(float deltaTime);
        void draw(sf::RenderWindow& window);
        float width();

    private:
        sf::Sprite enemy;
        bool movingRight;
        unsigned int gameRow;
        float speed;
        sf::Vector2f velocity;
        const float height = 90;
};

#endif
