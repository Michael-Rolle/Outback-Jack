// Headers
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "SplashScreenRenderer.h"
#include "PlayingFieldRenderer.h"
#include "Jack.h"
#include "PlatformController.h"
#include "Collisions.h"
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
    sf::Texture platformText;
    if(!platformText.loadFromFile("resources/log.png"))
        return EXIT_FAILURE;
    auto platforms = PlatformController(&platformText);
    auto collisionDetector = Collisions(Player_1, platforms, platforms.getPlatformRow(1).getPlatform(1).width(), 100.0f);

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
            platforms.update(deltaTime);
            collisionDetector.update();
        }

        // Render
        window.clear();
        if(isPlaying)
        {
            playingFieldRenderer.renderPlayingField(window);
            platforms.draw(window);
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
