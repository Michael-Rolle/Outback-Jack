#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <SFML/Graphics.hpp>

#define private public //for testing purposes
#include "../game-source-code/Jack.h"

//Global Constants
const float gameWidth = 1920;
const float gameHeight = 1080;

const sf::Event simulateKeypress(sf::Keyboard::Key key, bool alt, bool control, bool shift, bool system)
{
    sf::Event::KeyEvent data;
    data.code = key;
    data.alt = alt;
    data.control = control;
    data.shift = shift;
    data.system = system;

    sf::Event event;
    event.type = sf::Event::KeyPressed;
    event.key = data;
    return event;
}

TEST_CASE("Player spawns in the safe zone")
{
    sf::Texture jack_spritesheet;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    CHECK(player.jack.getPosition().y > (gameHeight/6.0f)*1);
    CHECK(player.jack.getPosition().y < (gameHeight/6.0f)*2);
}

TEST_CASE("Players height is 100 pixels")
{
    sf::Texture jack_spritesheet;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    CHECK(player.jack.getGlobalBounds().height/3.0f == 100.0f);
}

TEST_CASE("Players width is 100 pixels")
{
    sf::Texture jack_spritesheet;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    CHECK(player.jack.getGlobalBounds().width/3.0f == 100.0f);
}

TEST_CASE("Player can move right")
{
    sf::Texture jack_spritesheet;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    auto prvsPos = player.jack.getPosition().x;
    sf::Event event = simulateKeypress(sf::Keyboard::D, false, false, false, false);
    player.setMovement(event);
    sf::Clock clock1;
    sf::Clock clock2;
    while(clock1.getElapsedTime().asSeconds() <= 0.1f)
    {
       player.update(clock2.restart().asSeconds());
    }
    CHECK(player.jack.getPosition().x > prvsPos);
}

TEST_CASE("Player can move left")
{
    sf::Texture jack_spritesheet;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    auto prvsPos = player.jack.getPosition().x;
    sf::Event event = simulateKeypress(sf::Keyboard::A, false, false, false, false);
    player.setMovement(event);
    sf::Clock clock1;
    sf::Clock clock2;
    while(clock1.getElapsedTime().asSeconds() <= 0.1f)
    {
       player.update(clock2.restart().asSeconds());
    }
    CHECK(player.jack.getPosition().x < prvsPos);
}

TEST_CASE("Player can jump down")
{
    sf::Texture jack_spritesheet;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    auto previousPos = player.jack.getPosition().y;
    sf::Event event = simulateKeypress(sf::Keyboard::S, false, false, false, false);
    player.setMovement(event);
    sf::Clock clock1;
    sf::Clock clock2;
    while(clock1.getElapsedTime().asSeconds() <= 2)
    {
        player.update(clock2.restart().asSeconds());
    }
    CHECK(player.jack.getPosition().y > previousPos);
}

TEST_CASE("Player can jump up")
{
    sf::Texture jack_spritesheet;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    player.jack.setPosition(player.jack.getPosition().x, 450);
    player.gameRow = 2;
    auto previousPos = player.jack.getPosition().y;
    sf::Event event = simulateKeypress(sf::Keyboard::W, false, false, false, false);
    player.setMovement(event);
    sf::Clock clock1;
    sf::Clock clock2;
    while(clock1.getElapsedTime().asSeconds() <= 2)
    {
        player.update(clock2.restart().asSeconds());
    }
    CHECK(player.jack.getPosition().y < previousPos);
}

TEST_CASE("Player jumps down 180 pixels")
{
    sf::Texture jack_spritesheet;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    auto previousPos = player.jack.getPosition().y;
    sf::Event event = simulateKeypress(sf::Keyboard::S, false, false, false, false);
    player.setMovement(event);
    sf::Clock clock1;
    sf::Clock clock2;
    while(clock1.getElapsedTime().asSeconds() <= 2)
    {
        player.update(clock2.restart().asSeconds());
    }
    CHECK((int)player.jack.getPosition().y == (int)previousPos+180);
}

TEST_CASE("Player jumps up 180 pixels")
{
    sf::Texture jack_spritesheet;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    player.jack.setPosition(player.jack.getPosition().x, 450);
    player.gameRow = 2;
    auto previousPos = player.jack.getPosition().y;
    sf::Event event = simulateKeypress(sf::Keyboard::W, false, false, false, false);
    player.setMovement(event);
    sf::Clock clock1;
    sf::Clock clock2;
    while(clock1.getElapsedTime().asSeconds() <= 2)
    {
        player.update(clock2.restart().asSeconds());
    }
    CHECK((int)player.jack.getPosition().y == (int)previousPos-180);
}

TEST_CASE("Player can't move right out of bounds")
{
    sf::Texture jack_spritesheet;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    player.jack.setPosition(gameWidth, player.jack.getPosition().y);
    sf::Event event = simulateKeypress(sf::Keyboard::D, false, false, false, false);
    player.setMovement(event);
    sf::Clock clock1;
    sf::Clock clock2;
    while(clock1.getElapsedTime().asSeconds() <= 0.1f)
    {
       player.update(clock2.restart().asSeconds());
    }
    CHECK(player.jack.getPosition().x == gameWidth);
}

TEST_CASE("Player can't move left out of bounds")
{
    sf::Texture jack_spritesheet;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    player.jack.setPosition(0, player.jack.getPosition().y);
    sf::Event event = simulateKeypress(sf::Keyboard::A, false, false, false, false);
    player.setMovement(event);
    sf::Clock clock1;
    sf::Clock clock2;
    while(clock1.getElapsedTime().asSeconds() <= 0.1f)
    {
       player.update(clock2.restart().asSeconds());
    }
    CHECK(player.jack.getPosition().x == 0);
}
