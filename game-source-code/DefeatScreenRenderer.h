#ifndef DEFEATSCREENRENDERER_H
#define DEFEATSCREENRENDERER_H
#include <SFML/Graphics.hpp>

class DefeatScreenRenderer
{
    public:
        DefeatScreenRenderer(const float gameWidth, const float gameHeight);
        void draw(sf::RenderWindow& window);

    private:
        sf::Font font;
        sf::Text loseText;
        sf::Text restartText;
};

#endif // DEFEATSCREENRENDERER_H
