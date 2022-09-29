#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>


class Animation
{
    public:
        Animation(sf::Texture* texture, sf::Vector2u frameCount, float switchTime);
        ~Animation(){}
        void update(int row, float deltaTime, bool facingRight);
        sf::IntRect textRect;

    private:
        sf::Vector2u frameCount;
        sf::Vector2u currentFrame;
        float totalTime; //time since last changed frame
        float switchTime; //time between switching frames
};

#endif // ANIMATION_H
