#ifndef JACK_H
#define JACK_H
#include <SFML/Graphics.hpp>
#include "Animation.h";

class Jack
{
    public:
        Jack(sf::Texture* texture, sf::Vector2u frameCount, float switchTime, float speed);
        void update(float deltaTime);
        void draw(sf::RenderWindow& window);

    private:
        sf::Sprite jack;
        Animation animation;
        unsigned int row;
        float speed;
        bool facingRight;
};

#endif
