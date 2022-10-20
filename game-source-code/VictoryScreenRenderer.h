#ifndef VICTORYSCREENRENDERER_H
#define VICTORYSCREENRENDERER_H
#include <SFML/Graphics.hpp>

/*!
Draws the victory screen for when the player wins the game.
*/

class VictoryScreenRenderer
{
    public:
        VictoryScreenRenderer(const float gameWidth, const float gameHeight);
        void draw(sf::RenderWindow& window);
        /*!< Draws the text notifying the player they have won and the game can be restarted by pressing space, with reference to a RenderWindow. */

    private:
        sf::Font font;
        sf::Text winText;
        sf::Text restartText;
};

#endif // VICTORYSCREENRENDERER_H
