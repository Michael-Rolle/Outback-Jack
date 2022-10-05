#ifndef SCORE_H
#define SCORE_H
#include <SFML/Graphics.hpp>
#include "Jack.h"

class Score
{
    public:
        Score(const float gameWidth, const float gameHeight);
        void draw(sf::RenderWindow& window);
        void update(Jack& player);
        void reset();

    private:
        sf::Font font;
        sf::Text points;
        sf::Text label;
        int score;
};

#endif
