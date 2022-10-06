#include "DefeatScreenRenderer.h"

DefeatScreenRenderer::DefeatScreenRenderer(const float gameWidth, const float gameHeight)
{
    if(!font.loadFromFile("resources/I-Have-Bad-News.ttf"))
        throw "cannot load font";
    loseText.setFont(font);
    restartText.setFont(font);
    loseText.setString("You Lose!");
    restartText.setString("Press Space to Replay");
    loseText.setCharacterSize(100);
    restartText.setCharacterSize(50);
    loseText.setLetterSpacing(3);
    restartText.setLetterSpacing(3);
    loseText.setFillColor(sf::Color::White);
    loseText.setOutlineColor(sf::Color::Red);
    restartText.setFillColor(sf::Color::Red);
    loseText.setOutlineThickness(3);
    restartText.setOutlineThickness(2);
    restartText.setOutlineColor(sf::Color::White);
    loseText.setOrigin(loseText.getLocalBounds().width/2.0f, loseText.getLocalBounds().height/2.0f);
    restartText.setOrigin(restartText.getLocalBounds().width/2.0f, restartText.getLocalBounds().height/2.0f);
    loseText.setPosition(gameWidth/2.0f, 0.3*gameHeight);
    restartText.setPosition(gameWidth/2.0f, 0.6*gameHeight);
}

void DefeatScreenRenderer::draw(sf::RenderWindow& window)
{
    window.draw(loseText);
    window.draw(restartText);
}
