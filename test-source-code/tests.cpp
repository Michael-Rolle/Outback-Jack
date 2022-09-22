#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <SFML/Graphics.hpp>

#define private public //for testing purposes
#include "../game-source-code/Jack.h"

//Global Constants
const float gameWidth = 1920;
const float gameHeight = 1080;

const sf::Event simulateKeypress(sf::Keyboard::Key key)
{
    sf::Event event;
    event.type = sf::Event::KeyPressed;
    event.key.code = key;
    return event;
}

TEST_CASE("All assests load correctly")
{
    sf::Texture arrows;
    sf::Texture wasd;
    sf::Texture platform;
    sf::Texture jack;
    sf::Texture field;
    sf::Texture background;
    sf::Font font;

    CHECK(arrows.loadFromFile("resources/arrows.png"));
    CHECK(wasd.loadFromFile("resources/wasd.png"));
    CHECK(platform.loadFromFile("resources/basic_platform.png"));
    CHECK(jack.loadFromFile("resources/jack_frames.png"));
    CHECK(field.loadFromFile("resources/playingField.png"));
    CHECK(background.loadFromFile("resources/start_background.jpg"));
    CHECK(font.loadFromFile("resources/I-Have-Bad-News.ttf"));
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
    sf::Event event = simulateKeypress(sf::Keyboard::D);
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
    sf::Event event = simulateKeypress(sf::Keyboard::A);
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
    sf::Event event = simulateKeypress(sf::Keyboard::S);
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
    sf::Event event = simulateKeypress(sf::Keyboard::W);
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
    sf::Event event = simulateKeypress(sf::Keyboard::S);
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
    sf::Event event = simulateKeypress(sf::Keyboard::W);
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
