#include "SplashScreenRenderer.h"
#include <SFML/Graphics.hpp>

SplashScreenRenderer::SplashScreenRenderer(const float gameWidth, const float gameHeight)
{
    //Font
    if(!font.loadFromFile("resources/I-Have-Bad-News.ttf"))
        throw "cannot load font file";

    //Text
    title.setFont(font);
    startMessage.setFont(font);
    title.setCharacterSize(100);
    startMessage.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    startMessage.setFillColor(sf::Color::Red);
    title.setString("OUTBACK  JACK");
    startMessage.setString("Press  Space  to  Play");
    title.setLetterSpacing(3);
    startMessage.setLetterSpacing(3);
    title.setOutlineThickness(3);
    title.setOutlineColor(sf::Color::Red);
    startMessage.setOutlineThickness(2);
    startMessage.setOutlineColor(sf::Color::White);
    // Centre text
    sf::FloatRect titleRect = title.getLocalBounds();
    sf::FloatRect startRect = startMessage.getLocalBounds();
    title.setOrigin(titleRect.left + titleRect.width/2.0f, titleRect.top + titleRect.height/2.0f);
    title.setPosition(gameWidth/2, gameHeight/2 - title.getCharacterSize());
    startMessage.setOrigin(startRect.left + startRect.width/2.0f, startRect.top + startRect.height/2.0f);
    startMessage.setPosition(title.getPosition().x, title.getPosition().y + 2*title.getCharacterSize());

    //Background image
    if(!background.loadFromFile("resources/start_background.jpg"))
        throw "cannot load background image";
    backgroundImage.setTexture(background);
    backgroundImage.setScale(gameWidth/backgroundImage.getLocalBounds().width, gameHeight/backgroundImage.getLocalBounds().height);
    sf::FloatRect picRect = backgroundImage.getLocalBounds();
    backgroundImage.setOrigin(picRect.left + picRect.width/2.0f, picRect.top + picRect.height/2.0f);
    backgroundImage.setPosition(gameWidth/2.0f, gameHeight/2.0f);
}

void SplashScreenRenderer::renderSplashScreen(sf::RenderWindow& window)
{
    window.draw(backgroundImage);
    window.draw(title);
    window.draw(startMessage);
}
