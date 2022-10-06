#ifndef SPLASHSCREENRENDERER_H
#define SPLASHSCREENRENDERER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class SplashScreenRenderer
{
    public:
        SplashScreenRenderer(const float gameWidth, const float gameHeight);
        void draw(sf::RenderWindow& window);

    private:
        sf::Font font;
        sf::Text title;
        sf::Text startMessage;
        sf::Texture background;
        sf::Sprite backgroundImage;

        sf::Text player_1;
        sf::Text player_2;
        sf::Text controls_1_text;
        sf::Text controls_2_text;

        sf::Texture controls_1;
        sf::Sprite controls_1_Image;
        sf::Texture controls_2;
        sf::Sprite controls_2_Image;
};

#endif
