#ifndef SPLASHSCREENRENDERER_H
#define SPLASHSCREENRENDERER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/*!
Draws the splash screen detailing the title of the game and the controls for the player.
*/

class SplashScreenRenderer
{
    public:
        SplashScreenRenderer(const float gameWidth, const float gameHeight);
        void draw(sf::RenderWindow& window);
        /*!< Draws all text and images with reference to a RenderWindow. */

    private:
        sf::Font font;
        sf::Text title;
        sf::Text startMessage;
        sf::Texture background;
        sf::Sprite backgroundImage;

        sf::Text player_1;
        sf::Text player_2;
        sf::Text controls_1_text;
        sf::Text controls_1_shift;
        sf::Text controls_2_text;
        sf::Text controls_2_shift;

        sf::Texture controls_1;
        sf::Sprite controls_1_Image;
        sf::Texture controls_1_Shift;
        sf::Sprite controls_1_Shift_Image;
        sf::Texture controls_2;
        sf::Sprite controls_2_Image;
        sf::Texture controls_2_Shift;
        sf::Sprite controls_2_Shift_Image;
};

#endif
