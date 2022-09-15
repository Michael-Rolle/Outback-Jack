#include "Renderer.h"
#include <SFML/Graphics.hpp>

Renderer::Renderer(sf::RenderWindow window):
    //gameWidth = 1920;
    //gameHeight = 1080;
    //frameRate = 60;
    window_ = window;
{
    //Window
    //window.setView(sf::View(sf::FloatRect(0.0f, 0.0f, gameWidth, gameHeight)));
    //window.setFramerateLimit(frameRate);

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
    title.setPosition(window.getView().getCenter().x, window.getView().getCenter().y - title.getCharacterSize());
    startMessage.setOrigin(startRect.left + startRect.width/2.0f, startRect.top + startRect.height/2.0f);
    startMessage.setPosition(title.getPosition().x, title.getPosition().y + 2*title.getCharacterSize());

    //Background image
    sf::Texture background;
    if(!background.loadFromFile("resources/start_background.jpg"))
        throw "cannot load background image";
    backgroundImage = ;
    image.setScale(window.getView().getSize().x/image.getLocalBounds().width, window.getView().getSize().y/image.getLocalBounds().height);
    sf::FloatRect picRect = image.getLocalBounds();
    image.setOrigin(picRect.left + picRect.width/2, picRect.top + picRect.height/2);
    image.setPosition(window.getView().getCenter());
}

Renderer::renderSplashScreen()
{

}
