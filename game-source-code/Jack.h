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
        const sf::Vector2f padding{90, 80}; //Padding of character in each frame
        unsigned int row;
        float speed;
        bool facingRight;
};

#endif
