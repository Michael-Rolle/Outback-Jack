// Headers
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "SplashScreenRenderer.h"
#include "PlayingFieldRenderer.h"
#include "Jack.h"
#include "Platform.h"
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

    // Initialize the splash screen, playing field and Jack
    auto splashRenderer = SplashScreenRenderer(gameWidth, gameHeight);
    auto playingFieldRenderer = PlayingFieldRenderer(gameWidth, gameHeight);
    sf::Texture jack_spritesheet;
    if(!jack_spritesheet.loadFromFile("resources/jack_frames.png"))
        return EXIT_FAILURE;
    auto Player_1 = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    //auto platform = Platform(gameWidth, gameHeight);
    sf::Texture platformText;
    if(!platformText.loadFromFile("resources/log.png"))
        return EXIT_FAILURE;
    auto log1 = Platform(&platformText, 200.0f, true, 2);
    auto log2 = Platform(&platformText, 200.0f, false, 3);
    auto log3 = Platform(&platformText, 200.0f, true, 4);
    auto log4 = Platform(&platformText, 200.0f, false, 5);

    sf::Clock clock;
    float deltaTime = 0;
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
            }

            if(isPlaying)
            {
                Player_1.setMovement(event);
            }
        }

        if(isPlaying)
        {
            deltaTime = clock.restart().asSeconds();
            Player_1.update(deltaTime); //controls movement and animations
            log1.update(deltaTime);
            log2.update(deltaTime);
            log3.update(deltaTime);
            log4.update(deltaTime);
        }

        // Render
        window.clear();
        if(isPlaying)
        {
            playingFieldRenderer.renderPlayingField(window);
            //platform.renderPlatform(window);
            log1.draw(window);
            log2.draw(window);
            log3.draw(window);
            log4.draw(window);
            Player_1.draw(window);
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
