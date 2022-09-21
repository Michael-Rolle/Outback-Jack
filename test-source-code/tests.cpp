#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <SFML/Graphics.hpp>

#define private public //for testing purposes
#include "../game-source-code/Jack.h"

//Global Constants
const float gameWidth = 1920;
const float gameHeight = 1080;

TEST_CASE("Player spawns in the safe zone")
{
    sf::Texture jack_spritesheet;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    CHECK(player.jack.getPosition().y > (gameHeight/6.0f)*1);
    CHECK(player.jack.getPosition().y < (gameHeight/6.0f)*2);
}

/*TEST_CASE("Player can move right")
{
    sf::Texture jack_spritesheet;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    auto previousPos = player.jack.getPosition().x;

    sf::Clock clock;
    float deltaTime = 0;
    while(true)
    {
        deltaTime = clock.restart().asSeconds();
        player.update(deltaTime); //controls movement and animations
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            break;
    }

    CHECK(player.jack.getPosition().x > previousPos);
}*/
