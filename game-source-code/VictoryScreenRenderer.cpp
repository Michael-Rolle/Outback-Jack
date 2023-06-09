#include "VictoryScreenRenderer.h"

VictoryScreenRenderer::VictoryScreenRenderer(const float gameWidth, const float gameHeight)
{
    if(!font.loadFromFile("resources/I-Have-Bad-News.ttf"))
        throw "cannot load font";
    winText.setFont(font);
    restartText.setFont(font);
    winText.setString("You Win!");
    restartText.setString("Press Space to Replay");
    winText.setCharacterSize(100);
    restartText.setCharacterSize(50);
    winText.setLetterSpacing(3);
    restartText.setLetterSpacing(3);
    winText.setFillColor(sf::Color::White);
    winText.setOutlineColor(sf::Color::Red);
    restartText.setFillColor(sf::Color::Red);
    winText.setOutlineThickness(3);
    restartText.setOutlineThickness(2);
    restartText.setOutlineColor(sf::Color::White);
    winText.setOrigin(winText.getLocalBounds().width/2.0f, winText.getLocalBounds().height/2.0f);
    restartText.setOrigin(restartText.getLocalBounds().width/2.0f, restartText.getLocalBounds().height/2.0f);
    winText.setPosition(gameWidth/2.0f, 0.3*gameHeight);
    restartText.setPosition(gameWidth/2.0f, 0.6*gameHeight);
}

void VictoryScreenRenderer::draw(sf::RenderWindow& window)
{
    window.draw(winText);
    window.draw(restartText);
}
