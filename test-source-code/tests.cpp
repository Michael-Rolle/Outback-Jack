#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <SFML/Graphics.hpp>

#define private public //for testing purposes
#include "../game-source-code/Jack.h"
#include "../game-source-code/PlatformController.h"
#include "../game-source-code/Collisions.h"
#include "../game-source-code/Tent.h"
#include "../game-source-code/Enemy.h"
#include "../game-source-code/EnemyController.h"
#include "../game-source-code/EnemyCollisions.h"

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
    sf::Texture texture;
    sf::Font font;

    CHECK(texture.loadFromFile("resources/arrows.png"));
    CHECK(texture.loadFromFile("resources/wasd.png"));
    CHECK(texture.loadFromFile("resources/basic_platform.png"));
    CHECK(texture.loadFromFile("resources/jack_frames.png"));
    CHECK(texture.loadFromFile("resources/playingField.png"));
    CHECK(texture.loadFromFile("resources/start_background.jpg"));
    CHECK(texture.loadFromFile("resources/log.png"));
    CHECK(texture.loadFromFile("resources/white_log.png"));
    CHECK(texture.loadFromFile("resources/croc.png"));
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

TEST_CASE("Player can't jump up out of safe zone")
{
    sf::Texture jack_spritesheet;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    sf::Event event = simulateKeypress(sf::Keyboard::W);
    player.setMovement(event);
    CHECK_FALSE(player.isJumping);
}

TEST_CASE("Player can't jump down past bottom row")
{
    sf::Texture jack_spritesheet;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    player.jack.setPosition(player.jack.getPosition().x, 990);
    player.gameRow = 5;
    sf::Event event = simulateKeypress(sf::Keyboard::S);
    player.setMovement(event);
    CHECK_FALSE(player.isJumping);
}

TEST_CASE("Player can't move right out of bounds")
{
    sf::Texture jack_spritesheet;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    player.jack.setPosition(gameWidth-50, player.jack.getPosition().y);
    sf::Event event = simulateKeypress(sf::Keyboard::D);
    player.setMovement(event);
    sf::Clock clock1;
    sf::Clock clock2;
    while(clock1.getElapsedTime().asSeconds() <= 0.5f)
    {
       player.update(clock2.restart().asSeconds());
    }
    CHECK(player.jack.getPosition().x == gameWidth-50);
}

TEST_CASE("Player can't move left out of bounds")
{
    sf::Texture jack_spritesheet;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    player.jack.setPosition(50, player.jack.getPosition().y);
    sf::Event event = simulateKeypress(sf::Keyboard::A);
    player.setMovement(event);
    sf::Clock clock1;
    sf::Clock clock2;
    while(clock1.getElapsedTime().asSeconds() <= 0.5f)
    {
       player.update(clock2.restart().asSeconds());
    }
    CHECK(player.jack.getPosition().x == 50);
}

TEST_CASE("Platforms move in alternate directions")
{
    sf::Texture log;
    log.loadFromFile("resources/log.png");
    auto platformController = PlatformController(&log);
    auto rowOneDir = platformController.getPlatformRow(1)->movingRight;
    auto rowTwoDir = platformController.getPlatformRow(2)->movingRight;
    auto rowThreeDir = platformController.getPlatformRow(3)->movingRight;
    auto rowFourDir = platformController.getPlatformRow(4)->movingRight;
    CHECK(rowOneDir != rowTwoDir);
    CHECK(rowTwoDir != rowThreeDir);
    CHECK(rowThreeDir != rowFourDir);
}

TEST_CASE("Platforms can succesfully change colour")
{
    sf::Texture log;
    log.loadFromFile("resources/log.png");
    sf::Texture white_log;
    white_log.loadFromFile("resources/white_log.png");
    auto platformController = PlatformController(&log);
    platformController.changePlatformRowColour(1, &white_log, false);
    CHECK_FALSE(platformController.getPlatformRow(1)->isOriginalColour);
}

TEST_CASE("Player moves along with platform when on top of one")
{
    sf::Texture jack_spritesheet;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    sf::Texture log;
    log.loadFromFile("resources/log.png");
    auto tent = Tent(&log, 4, 4, 200.0f);
    auto platformController = PlatformController(&log);
    auto platformPositions = platformController.getPlatformPositions(1);
    auto collisionDetector = Collisions(platformController.getPlatformRow(1)->getPlatform(1).width(), 100.0f);
    player.jack.setPosition(platformPositions.back(), 450); //set Jack on top of a platform
    auto previousPos = player.getPositionX();
    player.gameRow = 2;
    sf::Clock clock1;
    sf::Clock clock2;
    float deltaTime;
    auto score = Score{1920, 1080};
    while(clock1.getElapsedTime().asSeconds() <= 0.5f)
    {
        deltaTime = clock2.restart().asSeconds();
        player.update(deltaTime);
        platformController.update(deltaTime);
        collisionDetector.update(player, &jack_spritesheet, platformController, &log, &log, tent, score);
    }
    CHECK(player.getPositionX() != previousPos);
}

TEST_CASE("Enemy can move right and left")
{
    sf::Texture enemyText;
    enemyText.loadFromFile("resources/croc.png");
    auto speed = 200.0f;
    auto movingRight = true;
    auto gameRow = 2u;
    auto enemy = Enemy(&enemyText, speed, movingRight, gameRow);
    auto startPos = enemy.getPositionX();
    sf::Clock clock1;
    sf::Clock clock2;
    float deltaTime;

    while(clock1.getElapsedTime().asSeconds() <= 0.1f)
    {
        deltaTime = clock2.restart().asSeconds();
        enemy.update(deltaTime);
    }
    CHECK(enemy.getPositionX() > startPos);

    enemy.movingRight = false;
    while(clock1.getElapsedTime().asSeconds() <= 0.3f)
    {
        deltaTime = clock2.restart().asSeconds();
        enemy.update(deltaTime);
    }
    CHECK(enemy.getPositionX() < startPos);
}

TEST_CASE("Enemies can kill Jack")
{
    sf::Texture enemyText;
    enemyText.loadFromFile("resources/croc.png");
    auto enemies = EnemyController(&enemyText, 1920);
    auto enemyCollisionDetector = EnemyCollisions(enemies.getEnemyRow(1)->getEnemy(1).width(), 150.0f);
    sf::Texture jack_spritesheet;
    sf::Texture deadJackText;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    deadJackText.loadFromFile("resources/dead_jack.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    player.jack.setPosition(1900.0f, 180.0f + 180.0f);
    sf::Texture kangarooSpritesheetText;
    kangarooSpritesheetText.loadFromFile("resources/kangaroo.png");
    auto kangaroo = Kangaroo{&kangarooSpritesheetText, sf::Vector2u{3,1}, 0.3f, 200.0f};
    sf::Clock clock1;
    sf::Clock clock2;
    float deltaTime;
    while(clock1.getElapsedTime().asSeconds() <= 0.1f)
    {
        deltaTime = clock2.restart().asSeconds();
        player.update(deltaTime);
        enemies.update(deltaTime);
        enemyCollisionDetector.update(player, &deadJackText, enemies, kangaroo);
    }
    CHECK(player.isAlive == false);
}

TEST_CASE("The Kangaroo can kill Jack")
{
    sf::Texture enemyText;
    enemyText.loadFromFile("resources/croc.png");
    auto enemies = EnemyController(&enemyText, 1920);
    auto enemyCollisionDetector = EnemyCollisions(enemies.getEnemyRow(1)->getEnemy(1).width(), 150.0f);
    sf::Texture jack_spritesheet;
    sf::Texture deadJackText;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    deadJackText.loadFromFile("resources/dead_jack.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    player.jack.setPosition(1900.0f, 180.0f + 90.0f);
    sf::Texture kangarooSpritesheetText;
    kangarooSpritesheetText.loadFromFile("resources/kangaroo.png");
    auto kangaroo = Kangaroo{&kangarooSpritesheetText, sf::Vector2u{3,1}, 0.3f, 200.0f};
    sf::Clock clock1;
    sf::Clock clock2;
    float deltaTime;
    while(clock1.getElapsedTime().asSeconds() <= 0.1f)
    {
        deltaTime = clock2.restart().asSeconds();
        player.update(deltaTime);
        enemies.update(deltaTime);
        enemyCollisionDetector.update(player, &deadJackText, enemies, kangaroo);
    }
    CHECK(player.isAlive == false);
}
