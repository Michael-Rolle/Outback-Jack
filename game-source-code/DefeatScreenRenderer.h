#ifndef DEFEATSCREENRENDERER_H
#define DEFEATSCREENRENDERER_H
#include <SFML/Graphics.hpp>

/*!
Displays a new, unique screen if the player dies. Notifies the player the game can be restarted.
*/

class DefeatScreenRenderer
{
    public:
        DefeatScreenRenderer(const float gameWidth, const float gameHeight);
        void draw(sf::RenderWindow& window);
        /*!< Takes in a reference to a RenderWindow to draw the respective text for if the player dies. */

    private:
        sf::Font font;
        sf::Text loseText;
        sf::Text restartText;
};

#endif // DEFEATSCREENRENDERER_H
