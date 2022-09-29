#ifndef VICTORYSCREENRENDERER_H
#define VICTORYSCREENRENDERER_H
#include <SFML/Graphics.hpp>

class VictoryScreenRenderer
{
    public:
        VictoryScreenRenderer(sf::Font* font);
        void draw(sf::RenderWindow& window);

    private:
        sf::Text winText;
        sf::Text restartText;
};

#endif // VICTORYSCREENRENDERER_H