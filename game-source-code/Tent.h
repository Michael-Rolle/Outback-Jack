#ifndef TENT_H
#define TENT_H
#include <SFML/Graphics.hpp>

class Tent
{
    public:
        Tent(sf::Texture* texture, unsigned int rows, unsigned int columns);
        Tent(){};
        void nextFrame();
        float getPositionX();
        float width();
        void draw(sf::RenderWindow& window);

    public:
        bool built;
    private:
        sf::Sprite tent;
        sf::Vector2u numFrames;
        sf::Vector2u currentFrame;
        sf::IntRect textRect;
        const float height = 200.0f;
};

#endif // TENT_H
