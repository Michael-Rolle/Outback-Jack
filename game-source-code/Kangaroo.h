#ifndef KANGAROO_H
#define KANGAROO_H
#include <SFML/Graphics.hpp>
#include "Jack.h"
#include "Animation.h"


class Kangaroo
{
    public:
        Kangaroo(sf::Texture* spritesheet, float height, float speed);
        float getPositionX(){ return joey.getPosition().x; }
        float width(){ return joey.getGlobalBounds().width; }
        void update(Jack& player);
        void draw(sf::RenderWindow& window);

    private:
        Animation animation;
        sf::Sprite joey;
        float height;
        float speed;
        bool movingRight;
};

#endif // KANGAROO_H
