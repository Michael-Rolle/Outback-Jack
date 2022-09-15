#ifndef RENDERER_H
#define RENDERER_H
#include <SFML/Graphics.hpp>


class Renderer
{
    public:
        Renderer(sf::RenderWindow window);
        void renderSplashScreen();

    private:
        sf::RenderWindow window_;
        sf::Font font;
        sf::Text title;
        sf::Text startMessage;
        //sf::Texture background;
        sf::Sprite backgroundImage;
        //const unsigned float gameWidth;
        //const unsigned float gameHeight;
        //const unsigned short frameRate;
};

#endif // RENDERER_H
