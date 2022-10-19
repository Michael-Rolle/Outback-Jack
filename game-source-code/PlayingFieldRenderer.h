#ifndef PLAYINGFIELDRENDERER_H
#define PLAYINGFIELDRENDERER_H
#include <SFML/Graphics.hpp>

/*!
Class responsible for drawing the background area or field. Only visible when the player starts the game.
*/

class PlayingFieldRenderer
{
    public:
        PlayingFieldRenderer(const float gameWidth, const float gameHeight);
        void draw(sf::RenderWindow& window); /*!< Draws the playing field with reference to a RenderWindow. */

    private:
        sf::Texture playingField;
        sf::Sprite playingFieldImage;
};

#endif
