#ifndef SCORE_H
#define SCORE_H
#include <SFML/Graphics.hpp>
#include "Jack.h"
#include "Temperature.h"
#include "GameSounds.h"
#include "FileReader.h"
#include <string>

/*!
Displays and keeps track of a players' score. Also displays the highest score achieved between games.
*/

using namespace std;

class Score
{
    public:
        Score(const float gameWidth, const float gameHeight);
        void draw(sf::RenderWindow& window); /*!< Draws the current score of the player and the high score with reference to a
        RenderWindow. */
        void update(Jack& player); /*!< Updates the respective players' score in increments of 10. */
        void updateFromTemp(Jack& player, Temperature& temperature); /*!< Updates the respective players' score from the Temperature
        object and if its a new high score, it is written to the text file. */
        void reset(); /*!< Resets the score for the player but maintains the value of the high score. */

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
