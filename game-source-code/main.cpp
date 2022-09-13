// Headers
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>

using namespace std;

// Global Constants
const int gameWidth = 1920;
const int gameHeight = 1080;
const int frameRate = 60;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Outback Jack");
    window.setView(sf::View(sf::FloatRect(0.0f, 0.0f, gameWidth, gameHeight)));
    window.setFramerateLimit(frameRate);

    // Load the text font
    sf::Font font;
    if(!font.loadFromFile("resources/I-Have-Bad-News.ttf"))
        return EXIT_FAILURE;

    // Initialize the start screen
    sf::Text title;
    sf::Text startMessage;
    title.setFont(font);
    startMessage.setFont(font);
    title.setCharacterSize(40);
    startMessage.setCharacterSize(20);
    title.setPosition(gameWidth/2.f, gameHeight/2.f);
    startMessage.setPosition(title.getPosition().x, title.getPosition().y + 2*title.getCharacterSize());
    title.setFillColor(sf::Color::White);
    startMessage.setFillColor(sf::Color::Red);
    title.setString("OUTBACK JACK");
    startMessage.setString("Press Space to Play");
    title.setLetterSpacing(3);
    startMessage.setLetterSpacing(3);
    title.setOutlineThickness(2);
    title.setOutlineColor(sf::Color::Red);

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
            window.draw(title);
            window.draw(startMessage);
        }
        window.display();
    }

    return EXIT_SUCCESS;
}
