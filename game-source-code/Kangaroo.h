#ifndef KANGAROO_H
#define KANGAROO_H
#include <SFML/Graphics.hpp>
#include "Jack.h"
#include "Animation.h"


class Kangaroo
{
    public:
        Kangaroo(sf::Texture* spritesheet, sf::Vector2u frameCount, float switchTime, float speed);
        Kangaroo();
        float getPositionX(){ return joey.getPosition().x; }
        float width(){ return joey.getGlobalBounds().width; }
        void update(Jack& player, float deltaTime);
        void draw(sf::RenderWindow& window);

    private:
        Animation animation;
        sf::Sprite joey;
        float height;
        float speed;
        bool movingRight;
        unsigned int frameRow;
        sf::Vector2f velocity;
};

#endif // KANGAROO_H
