// Headers
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "SplashScreenRenderer.h"
#include "Jack.h"
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

    // Initialize the splash screen and Jack
    auto splashRenderer = SplashScreenRenderer(gameWidth, gameHeight);
    auto Player_1 = Jack(gameWidth, gameHeight, window);

    //Movement
    const int playerSpeed = 0.15*gameWidth;

    sf::Clock clock;
    bool isPlaying = false;
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
                break;
            }

            // Space pressed, start game
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isPlaying)
            {
                isPlaying = true;
                break;
            }
        }

        if(isPlaying)
        {
            float deltaTime = clock.restart().asSeconds();
            auto JackRect = Player_1.getJackLocalBounds();
            auto x = Player_1.getJackPositionX();
            auto y = Player_1.getJackPositionY();

            // Player movement
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && x + JackRect.width/2 < gameWidth)
            {
                Player_1.moveJack(playerSpeed, deltaTime, 'D');
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && x - JackRect.width/2 > 0.f)
            {
                Player_1.moveJack(playerSpeed, deltaTime, 'A');
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && y - JackRect.height/2 > 0.f)
            {
                Player_1.moveJack(playerSpeed, deltaTime, 'W');
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && y + JackRect.height/2 < gameHeight)
            {
                Player_1.moveJack(playerSpeed, deltaTime, 'S');
            }
        }

        // Render
        window.clear();
        if(isPlaying)
        {
            //draw the playing field
            Player_1.renderJack(window);
        }
        else
        {
            //draw the splash screen
            splashRenderer.renderSplashScreen(window);
        }
        window.display();
    }

    return EXIT_SUCCESS;
}
