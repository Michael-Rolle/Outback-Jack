#ifndef SCORE_H
#define SCORE_H
#include <SFML/Graphics.hpp>
#include "Jack.h"
#include "Temperature.h"
#include "GameSounds.h"
#include "FileReader.h"

class Score
{
    public:
        Score(const float gameWidth, const float gameHeight);
        void draw(sf::RenderWindow& window);
        void update(Jack& player);
        void updateFromTemp(Jack& player, Temperature& temperature);
        void reset();

    private:
        sf::Font font;
        sf::Text points;
        sf::Text label;
        sf::Text highScoreText;
        FileReader highScoreFileReader;
        int score;
        int highScore;
};

#endif
