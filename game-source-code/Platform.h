#ifndef PLATFORM_H
#define PLATFORM_H
#include <SFML/Graphics.hpp>


class Platform
{
    public:
        Platform(sf::Texture* texture, float speed, bool movingRight, unsigned int gameRow);
        void changeDirection();
        void setPositionX(float x);
        void getPositionX();
        void update(float deltaTime);
        void draw(sf::RenderWindow& window);
        float width();
        //isActive(Jack jack);
        //void renderPlatform(sf::RenderWindow& window);

    private:
        //bool active;
        //sf::Texture platform;
        sf::Sprite platform;
        bool movingRight;
        unsigned int gameRow;
        float speed;
        sf::Vector2f velocity;
        const float height = 90;
};

#endif
