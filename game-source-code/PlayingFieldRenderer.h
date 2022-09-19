#ifndef PLAYINGFIELDRENDERER_H
#define PLAYINGFIELDRENDERER_H
#include <SFML/Graphics.hpp>


class PlayingFieldRenderer
{
    public:
        PlayingFieldRenderer(const float gameWidth, const float gameHeight);
        void renderPlayingField(sf::RenderWindow& window);

    private:
        sf::Texture playingField;
        sf::Sprite playingFieldImage;
};

#endif
