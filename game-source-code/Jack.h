#ifndef JACK_H
#define JACK_H
#include <SFML/Graphics.hpp>

class Jack
{
    public:
        Jack(const float gameWidth, const float gameHeight, sf::RenderWindow& window);
        sf::FloatRect getJackLocalBounds();
        float getJackPositionX();
        float getJackPositionY();
        void moveJack(const float playerSpeed, const float deltaTime, const float gameWidth, const float gameHeight);
        void renderJack(sf::RenderWindow& window);

    private:
        sf::Texture jack_standing;
        sf::Sprite jack;
        sf::FloatRect jackRect;
};

#endif
