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

    // Initialize the splash screen
    auto splashRenderer = SplashScreenRenderer(gameWidth, gameHeight);

    //Load resources
    sf::Texture jack_standing;
    if(!jack_standing.loadFromFile("resources/jack.png"))
        return EXIT_FAILURE;
    sf::Sprite Jack;
    Jack.setTexture(jack_standing);

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
                sf::FloatRect jackRect = Jack.getLocalBounds();
                Jack.setOrigin(jackRect.left + jackRect.width/2, jackRect.top + jackRect.height/2);
                Jack.setPosition(window.getView().getCenter().x, window.getView().getCenter().y - 0.75*(gameHeight/2));
                Jack.setScale(0.1*(gameHeight/jackRect.height), 0.1*(gameHeight/jackRect.height));
                break;
            }
        }

        if(isPlaying)
        {
            float deltaTime = clock.restart().asSeconds();
            auto JackRect = Jack.getLocalBounds();
            // Player movement
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && Jack.getPosition().x + JackRect.width/2 < gameWidth)
            {
                Jack.move(playerSpeed*deltaTime, 0.f);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && Jack.getPosition().x - JackRect.width/2 > 0.f)
            {
                Jack.move(-playerSpeed*deltaTime, 0.f);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && Jack.getPosition().y - JackRect.height/2 > 0.f)
            {
                Jack.move(0.f, -playerSpeed*deltaTime);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && Jack.getPosition().y + JackRect.width/2 < gameHeight)
            {
                Jack.move(0.f, playerSpeed*deltaTime);
            }
        }

        // Render
        window.clear();
        if(isPlaying)
        {
            //draw the playing field
            window.draw(Jack);
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
