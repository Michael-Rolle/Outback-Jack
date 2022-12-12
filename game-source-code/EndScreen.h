#ifndef ENDSCREEN_H
#define ENDSCREEN_H
#include <SFML/Graphics.hpp>
#include "PlayerNumber.h"

class EndScreen
{
    public:
        EndScreen(const float gameWidth, const float gameHeight);
        void displayWin(PlayerNumber num);
        void draw(sf::RenderWindow& window);

    private:
        sf::Font font;
        sf::Text text;
        sf::Text replayText;
};

#endif // ENDSCREEN_H
