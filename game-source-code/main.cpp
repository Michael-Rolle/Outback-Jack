// Headers
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>

using namespace std;

// Global Constants
const int gameWidth = 1280;
const int gameHeight = 720;
const int frameRate = 60;

int main()
{
    sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Outback Jack");
    window.setFramerateLimit(frameRate);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }
    }

    return 0;
}
