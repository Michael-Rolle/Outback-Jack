// Headers
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "SplashScreenRenderer.h"
#include "PlayingFieldRenderer.h"
#include "Jack.h"
#include "PlatformController.h"
#include "Collisions.h"
#include "Enemy.h"
#include "Temperature.h"
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

    // Initialize the splash screen, playing field, Jack, and platforms
    auto splashRenderer = SplashScreenRenderer(gameWidth, gameHeight);
    auto playingFieldRenderer = PlayingFieldRenderer(gameWidth, gameHeight);

    sf::Texture jack_spritesheet;
    if(!jack_spritesheet.loadFromFile("resources/jack_frames.png"))
        return EXIT_FAILURE;

    auto Player_1 = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    sf::Texture log;
    if(!log.loadFromFile("resources/log.png"))
        return EXIT_FAILURE;
    auto platforms = PlatformController(&log);

    sf::Texture croc;
    if(!croc.loadFromFile("resources/croc.png"))
        return EXIT_FAILURE;
    auto crocs = Enemy(&croc, 500.0f, true, 1);

    auto collisionDetector = Collisions(platforms.getPlatformRow(1)->getPlatform(1).width(), 100.0f);

    sf::Texture white_log;
    if(!white_log.loadFromFile("resources/white_log.png"))
        return EXIT_FAILURE;

    sf::Clock clock;
    float deltaTime = 0;
    bool isPlaying = false;

    auto temperature = Temperature(gameWidth, gameHeight);

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
            platforms.update(deltaTime);
            collisionDetector.update(Player_1, platforms, &log, &white_log);
            temperature.update(window, deltaTime);
        }

        // Render
        window.clear();
        if(isPlaying)
        {
            playingFieldRenderer.renderPlayingField(window);
            crocs.draw(window);
            platforms.draw(window);
            Player_1.draw(window);
            temperature.draw(window);
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
