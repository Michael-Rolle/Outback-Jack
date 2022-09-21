#ifndef SPLASHSCREENRENDERER_H
#define SPLASHSCREENRENDERER_H
#include <SFML/Graphics.hpp>


class SplashScreenRenderer
{
    public:
        SplashScreenRenderer(const float gameWidth, const float gameHeight);
        void renderSplashScreen(sf::RenderWindow& window);

    private:
        sf::Font font;
        sf::Text title;
        sf::Text startMessage;
        sf::Texture background;
        sf::Sprite backgroundImage;

        sf::Text player_1;
        sf::Text player_2;
        sf::Text up;
        sf::Text down;
        sf::Text left;
        sf::Text right;

        sf::Texture controls_1;
        sf::Sprite controls_1_Image;
        sf::Texture controls_2;
        sf::Sprite controls_2_Image;
};

#endif
