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
};

#endif
