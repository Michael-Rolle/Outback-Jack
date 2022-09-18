// Headers
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "SplashScreenRenderer.h"
#include "Jack.h"
//#include "Animation.h"
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
    sf::Texture jack_spritesheet;
    if(!jack_spritesheet.loadFromFile("resources/jack_frames.png"))
        throw "cannot load texture file";
    //auto Player_1 = Jack(&jack_spritesheet, gameWidth, gameHeight, window);
    auto Player_1 = Jack(&jack_spritesheet, sf::Vector2u(3,3), 0.3f, 300.0f);

    // Movement
    //const float playerSpeed = 0.15*gameWidth;
    //sf::IntRect rect(256, 0, 256, 256);
    sf::Clock movement_clock;
    float deltaTimeMovement = 0;
    //int prev = 0;

    // Animation
    //auto jack_animation = Animation{&jack_spritesheet, sf::Vector2u(3, 3), 0.3f};
    sf::Clock animation_clock;
    float deltaTimeAnimation = 0;

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
            deltaTimeMovement = movement_clock.restart().asSeconds();
            //Player_1.moveJack(playerSpeed, deltaTimeMovement, gameWidth, gameHeight, animation_clock);

            deltaTimeAnimation = animation_clock.restart().asSeconds();
            //jack_animation.update(0, deltaTimeAnimation, false);
            //Player_1.setTextureRect(jack_animation.textRect);

            Player_1.update(deltaTimeAnimation);

            //Animation
            /*if(animation_clock.getElapsedTime().asSeconds() > 0.3f)
            {
                if(rect.left == 512)
                {
                    rect.left -= 256;
                    prev = 512;
                }
                else if(rect.left == 0)
                {
                    rect.left += 256;
                    prev = 0;
                }
                else
                {
                    if(prev == 0)
                    {
                        rect.left += 256;
                    }
                    else
                    {
                        rect.left -= 256;
                    }
                }

                Player_1.setTextureRect(rect);
                animation_clock.restart();
            }*/
        }

        // Render
        window.clear();
        if(isPlaying)
        {
            //draw the playing field
            //Player_1.renderJack(window);
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
