// Headers
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "SplashScreenRenderer.h"
#include <cstdlib>
#include <iostream>

using namespace std;

// Global Constants
const float gameWidth = 1920;
const float gameHeight = 1080;
const unsigned short frameRate = 60;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Outback Jack");
    window.setView(sf::View(sf::FloatRect(0.0f, 0.0f, gameWidth, gameHeight)));
    window.setFramerateLimit(frameRate);

    /*// Load the text font
    sf::Font font;
    if(!font.loadFromFile("resources/I-Have-Bad-News.ttf"))
        return EXIT_FAILURE;

    // Initialize the start screen
    // Text
    sf::Text title;
    sf::Text startMessage;
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
    // Background image
    sf::Texture background;
    if(!background.loadFromFile("resources/start_background.jpg"))
        return EXIT_FAILURE;
    sf::Sprite image(background);
    image.setScale(window.getView().getSize().x/image.getLocalBounds().width, window.getView().getSize().y/image.getLocalBounds().height);
    sf::FloatRect picRect = image.getLocalBounds();
    image.setOrigin(picRect.left + picRect.width/2, picRect.top + picRect.height/2);
    image.setPosition(window.getView().getCenter());*/

    auto splashRenderer = SplashScreenRenderer(gameWidth, gameHeight);

    bool isPlaying = false;
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }

        // Render
        window.clear();
        if(isPlaying)
        {

        }
        else
        {
            /*window.draw(image);
            window.draw(title);
            window.draw(startMessage);*/
            splashRenderer.renderSplashScreen(window);
        }
        window.display();
    }

    return EXIT_SUCCESS;
}
