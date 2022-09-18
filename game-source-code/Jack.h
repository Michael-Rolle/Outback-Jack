#ifndef JACK_H
#define JACK_H
#include <SFML/Graphics.hpp>
#include "Animation.h";

class Jack
{
    public:
        //Jack(const sf::Texture* jack_spritesheet, const float gameWidth, const float gameHeight, sf::RenderWindow& window);
        Jack(sf::Texture* texture, sf::Vector2u frameCount, float switchTime, float speed);
        void update(float deltaTime);
        void draw(sf::RenderWindow& window);
        //sf::FloatRect getJackLocalBounds();
        //float getJackPositionX();
        //float getJackPositionY();
        //sf::IntRect getTextureRect();
        //void moveJack(const float playerSpeed, const float deltaTime, const float gameWidth, const float gameHeight, sf::Clock& clock);
        //void renderJack(sf::RenderWindow& window);
        //void setTextureRect(sf::IntRect rect);
        //void playWalkAnimation(sf::Clock& clock);

    private:
        //sf::Texture jack_spritesheet;
        //sf::IntRect textureRect;
        sf::Sprite jack;
        Animation animation;
        //sf::FloatRect jackRect;
        const sf::Vector2f padding{90, 80}; //Padding of character in each frame
        unsigned int row;
        float speed;
        bool facingRight;
};

#endif
