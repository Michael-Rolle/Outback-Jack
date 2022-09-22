#include "PlayingFieldRenderer.h"
#include <SFML/Graphics.hpp>

PlayingFieldRenderer::PlayingFieldRenderer(const float gameWidth, const float gameHeight)
{
    //Playing field image
    if(!playingField.loadFromFile("resources/playingField.png"))
        throw "cannot load playing field image";
    playingFieldImage.setTexture(playingField);
    playingFieldImage.setScale(gameWidth/playingFieldImage.getLocalBounds().width, gameHeight/playingFieldImage.getLocalBounds().height);
    sf::FloatRect fieldRect = playingFieldImage.getLocalBounds();
    playingFieldImage.setOrigin(fieldRect.left + fieldRect.width/2.0f, fieldRect.top + fieldRect.height/2.0f);
    playingFieldImage.setPosition(gameWidth/2.0f, gameHeight/2.0f);
}

void PlayingFieldRenderer::renderPlayingField(sf::RenderWindow& window)
{
    window.draw(playingFieldImage);
}
