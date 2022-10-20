#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <SFML/Graphics.hpp>

#define private public //for testing purposes
#include "../game-source-code/Jack.h"
#include "../game-source-code/PlatformController.h"
#include "../game-source-code/Collisions.h"
#include "../game-source-code/PointCollisions.h"
#include "../game-source-code/Tent.h"
#include "../game-source-code/Enemy.h"
#include "../game-source-code/EnemyRow.h"
#include "../game-source-code/EnemyController.h"
#include "../game-source-code/EnemyCollisions.h"
#include "../game-source-code/Kangaroo.h"
#include "../game-source-code/FishController.h"

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
    sf::SoundBuffer sound;

    CHECK(texture.loadFromFile("resources/arrows.png"));
    CHECK(texture.loadFromFile("resources/wasd.png"));
    CHECK(texture.loadFromFile("resources/Shift.png"));
    CHECK(texture.loadFromFile("resources/jack_frames.png"));
    CHECK(texture.loadFromFile("resources/burnt_jack.png"));
    CHECK(texture.loadFromFile("resources/dead_jack.png"));
    CHECK(texture.loadFromFile("resources/playingField.png"));
    CHECK(texture.loadFromFile("resources/start_background.jpg"));
    CHECK(texture.loadFromFile("resources/wide_log.png"));
    CHECK(texture.loadFromFile("resources/wide_log_white.png"));
    CHECK(texture.loadFromFile("resources/croc.png"));
    CHECK(texture.loadFromFile("resources/Fish.png"));
    CHECK(texture.loadFromFile("resources/kangaroo.png"));
    CHECK(texture.loadFromFile("resources/tent.png"));
    CHECK(font.loadFromFile("resources/I-Have-Bad-News.ttf"));
    CHECK(sound.loadFromFile("resources/05 Den of Thieves.wav"));
    CHECK(sound.loadFromFile("resources/18 The Archives.wav"));
    CHECK(sound.loadFromFile("resources/bonus.wav"));
    CHECK(sound.loadFromFile("resources/completion-of-a-level.wav"));
    CHECK(sound.loadFromFile("resources/landing.wav"));
    CHECK(sound.loadFromFile("resources/ominous-drums.wav"));
    CHECK(sound.loadFromFile("resources/quick-jump.wav"));
    CHECK(sound.loadFromFile("resources/score-increasing.wav"));
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
    auto gameSounds = GameSounds();
    player.setMovement(event, gameSounds);
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
    auto gameSounds = GameSounds();
    player.setMovement(event, gameSounds);
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
    auto gameSounds = GameSounds();
    player.setMovement(event, gameSounds);
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
    auto gameSounds = GameSounds();
    player.setMovement(event, gameSounds);
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
    auto gameSounds = GameSounds();
    player.setMovement(event, gameSounds);
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
    auto gameSounds = GameSounds();
    player.setMovement(event, gameSounds);
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
    auto gameSounds = GameSounds();
    player.setMovement(event, gameSounds);
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
    auto gameSounds = GameSounds();
    player.setMovement(event, gameSounds);
    CHECK_FALSE(player.isJumping);
}

TEST_CASE("Player can't move right out of bounds")
{
    sf::Texture jack_spritesheet;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    player.jack.setPosition(gameWidth-50, player.jack.getPosition().y);
    sf::Event event = simulateKeypress(sf::Keyboard::D);
    auto gameSounds = GameSounds();
    player.setMovement(event, gameSounds);
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
    auto gameSounds = GameSounds();
    player.setMovement(event, gameSounds);
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
    log.loadFromFile("resources/wide_log.png");
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
    log.loadFromFile("resources/wide_log.png");
    sf::Texture white_log;
    white_log.loadFromFile("resources/wide_log_white.png");
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
    log.loadFromFile("resources/wide_log.png");
    auto tent = Tent(&log, 4, 4, 200.0f);
    auto platformController = PlatformController(&log);
    auto platformPositions = platformController.getPlatformPositions(1);
    auto collisionDetector = Collisions(platformController.getPlatformRow(1)->getPlatform(1).width(), 100.0f);
    auto gameSounds = GameSounds();
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
        collisionDetector.update(player, &jack_spritesheet, platformController, &log, &log, tent, score, gameSounds);
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

TEST_CASE("Enemy loops around right edge of the screen")
{
    sf::Texture enemyText;
    enemyText.loadFromFile("resources/croc.png");
    const unsigned int numEnemies = 1;
    const float spacing = 10.0;
    const unsigned int gameRow = 2u;
    const bool movingRight = true;
    float pos = 1910.0;
    auto enemyRow = EnemyRow(&enemyText, numEnemies, spacing, gameRow, movingRight, pos);
    auto prevPos = enemyRow.enemyPositions();
    auto tempPrev = prevPos[0];
    vector<float> currPos;
    auto tempCurr = 0.0f;
    sf::Clock clock1;
    sf::Clock clock2;
    float deltaTime;
    while(clock1.getElapsedTime().asSeconds() <= 1.0f)
    {
        deltaTime = clock2.restart().asSeconds();
        enemyRow.update(deltaTime);
        currPos = enemyRow.enemyPositions();
    }
    tempCurr = currPos[0];
    CHECK(tempCurr < tempPrev);
}

TEST_CASE("Enemy loops around left edge of the screen")
{
    sf::Texture enemyText;
    enemyText.loadFromFile("resources/croc.png");
    const unsigned int numEnemies = 1;
    const float spacing = 10.0;
    const unsigned int gameRow = 2u;
    const bool movingRight = false;
    float pos = 10.0;
    auto enemyRow = EnemyRow(&enemyText, numEnemies, spacing, gameRow, movingRight, pos);
    auto prevPos = enemyRow.enemyPositions();
    auto tempPrev = prevPos[0];
    vector<float> currPos;
    auto tempCurr = 0.0f;
    sf::Clock clock1;
    sf::Clock clock2;
    float deltaTime;
    while(clock1.getElapsedTime().asSeconds() <= 1.0f)
    {
        deltaTime = clock2.restart().asSeconds();
        enemyRow.update(deltaTime);
        currPos = enemyRow.enemyPositions();
    }
    tempCurr = currPos[0];
    CHECK(tempCurr > tempPrev);
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

TEST_CASE("Fish can move") // fish direction is random, therefore testing if they are capable of movement
{
    sf::Texture fishText;
    fishText.loadFromFile("resources/Fish.png");
    auto fishRow = FishController(&fishText, 1, 50.0f);
    auto prevPos = fishRow.fishPositions();
    auto tempPrev = prevPos[0];
    vector<float> currPos;
    auto tempCurr = 0.0f;
    sf::Clock clock1;
    sf::Clock clock2;
    float deltaTime;
    while(clock1.getElapsedTime().asSeconds() <= 1.0f)
    {
        deltaTime = clock2.restart().asSeconds();
        fishRow.update(deltaTime);
        currPos = fishRow.fishPositions();
    }
    tempCurr = currPos[0];
    CHECK(tempCurr != tempPrev);
}

TEST_CASE("Fish can loop around the edge of the screen")
{
    sf::Texture fishText;
    fishText.loadFromFile("resources/Fish.png");
    auto numFish = 1;
    auto fishRow = FishController(&fishText, numFish, 50.0f);
    if(fishRow.movingRight)
        fishRow.fishRow.at(0)->setPositionX(gameWidth);
    else
        fishRow.fishRow.at(0)->setPositionX(0);
    auto prevPos = fishRow.fishPositions().front();
    sf::Clock clock1;
    sf::Clock clock2;
    float deltaTime;
    while(clock1.getElapsedTime().asSeconds() <= 0.5f)
    {
        deltaTime = clock2.restart().asSeconds();
        fishRow.update(deltaTime);
    }
    if(fishRow.movingRight)
        CHECK(fishRow.fishPositions().front() < prevPos);
    else
        CHECK(fishRow.fishPositions().front() > prevPos);
}

TEST_CASE("Kangaroo can move right and left")
{
    sf::Texture jack_spritesheet;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    player.jack.setPosition(1900.0f, 180.0f + 180.0f);
    player.gameRow = 3u;
    sf::Texture kangarooSpritesheetText;
    kangarooSpritesheetText.loadFromFile("resources/kangaroo.png");
    auto kangaroo = Kangaroo{&kangarooSpritesheetText, sf::Vector2u{3,1}, 0.3f, 200.0f};
    auto startPos = kangaroo.joey.getPosition().x;
    sf::Clock clock1;
    sf::Clock clock2;
    float deltaTime;

    kangaroo.movingRight = true;
    while(clock1.getElapsedTime().asSeconds() <= 0.1f)
    {
        deltaTime = clock2.restart().asSeconds();
        kangaroo.update(player, deltaTime);
    }
    CHECK(kangaroo.joey.getPosition().x  > startPos);

    kangaroo.movingRight = false;
    while(clock1.getElapsedTime().asSeconds() <= 0.3f)
    {
        deltaTime = clock2.restart().asSeconds();
        kangaroo.update(player, deltaTime);
    }
    CHECK(kangaroo.joey.getPosition().x < startPos);
}

TEST_CASE("Kangaroo can't move out of bounds")
{
    sf::Texture jack_spritesheet;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    player.jack.setPosition(1900.0f, 180.0f + 180.0f);
    player.gameRow = 3u;
    sf::Texture kangarooSpritesheetText;
    kangarooSpritesheetText.loadFromFile("resources/kangaroo.png");
    auto kangaroo = Kangaroo{&kangarooSpritesheetText, sf::Vector2u{3,1}, 0.3f, 200.0f};
    sf::Clock clock1;
    sf::Clock clock2;
    float deltaTime;

    kangaroo.movingRight = true;
    kangaroo.joey.setPosition(1910, 270);
    while(clock1.getElapsedTime().asSeconds() <= 0.5f)
    {
        deltaTime = clock2.restart().asSeconds();
        kangaroo.update(player, deltaTime);
    }
    CHECK(kangaroo.joey.getPosition().x  <= gameWidth);

    kangaroo.joey.setPosition(10, 270);
    kangaroo.movingRight = false;
    while(clock1.getElapsedTime().asSeconds() <= 0.5f)
    {
        deltaTime = clock2.restart().asSeconds();
        kangaroo.update(player, deltaTime);
    }
    CHECK(kangaroo.joey.getPosition().x >= 0.0f);
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

TEST_CASE("Platform direction can be switched by Jack")
{
    sf::Texture jack_spritesheet;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    sf::Texture log;
    log.loadFromFile("resources/wide_log.png");
    auto tent = Tent(&log, 4, 4, 200.0f);
    auto platformController = PlatformController(&log);
    auto platformPositions = platformController.getPlatformPositions(1);
    auto collisionDetector = Collisions(platformController.getPlatformRow(1)->getPlatform(1).width(), 100.0f);
    auto gameSounds = GameSounds();
    player.jack.setPosition(platformPositions.back(), 450); //set Jack on top of a platform
    player.gameRow = 2;
    auto prevDir = platformController.getPlatformRow(1)->getPlatform(1).movingRight;
    sf::Event event = simulateKeypress(sf::Keyboard::LShift);
    player.setMovement(event, gameSounds);
    sf::Clock clock1;
    sf::Clock clock2;
    float deltaTime;
    bool newDir = false;
    auto score = Score{1920, 1080};
    while(clock1.getElapsedTime().asSeconds() <= 0.00001f)
    {
        deltaTime = clock2.restart().asSeconds();
        player.update(deltaTime);
        platformController.update(deltaTime);
        collisionDetector.update(player, &jack_spritesheet, platformController, &log, &log, tent, score, gameSounds);
        newDir = platformController.getPlatformRow(1)->getPlatform(1).movingRight;
    }
    CHECK(newDir != prevDir);
}

TEST_CASE("Temperature increases with time")
{
    sf::Texture jack_spritesheet;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    auto temperature = Temperature{1920, 1080};
    auto previousTemp = temperature.temp;
    float deltaTime = 10;
    temperature.update(player, &jack_spritesheet, deltaTime);
    auto currentTemp = temperature.temp;
    CHECK(currentTemp > previousTemp);
}

TEST_CASE("When temperature gets to 50 degrees celsius, the player dies")
{
    sf::Texture jack_spritesheet;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    auto temperature = Temperature{1920, 1080};
    float deltaTime = 50;
    temperature.update(player, &jack_spritesheet, deltaTime);
    CHECK_FALSE(player.isAlive);
}

TEST_CASE("Tent adds a block when player jumps on an untouched platform")
{
    sf::Texture jack_spritesheet, tentText;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    tentText.loadFromFile("resources/tent.png");
    auto tent = Tent(&tentText, 4, 4, 200.0f);
    auto prevFrameX = tent.currentFrame.x;
    sf::Texture log;
    log.loadFromFile("resources/wide_log.png");
    auto score = Score{1920, 1080};
    auto platformController = PlatformController(&log);
    auto platformPositions = platformController.getPlatformPositions(1);
    auto collisionDetector = Collisions(platformController.getPlatformRow(1)->getPlatform(1).width(), 100.0f);
    auto gameSounds = GameSounds();
    player.jack.setPosition(platformPositions.back(), 450); //set Jack on top of a platform
    player.gameRow = 2;
    collisionDetector.update(player, &jack_spritesheet, platformController, &tentText, &tentText, tent, score, gameSounds);
    CHECK(tent.currentFrame.x != prevFrameX);
}

TEST_CASE("Player can win the game when the tent is fully built")
{
    sf::Texture jack_spritesheet, tentText;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    tentText.loadFromFile("resources/tent.png");
    auto tent = Tent{&tentText, 4, 4, 200.0f};
    tent.currentFrame = sf::Vector2u(3, 4);
    tent.nextFrame();
    player.jack.setPosition(tent.getPositionX(), 270);
    player.gameRow = 1;
    sf::Event event = simulateKeypress(sf::Keyboard::W);
    CHECK(player.wonGame(event, tent));
}

TEST_CASE("Score increases when player jumps onto an untouched platform")
{
    sf::Texture jack_spritesheet, tentText;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    tentText.loadFromFile("resources/tent.png");
    auto tent = Tent(&tentText, 4, 4, 200.0f);
    auto prevScore = player.score;
    sf::Texture log;
    log.loadFromFile("resources/wide_log.png");
    auto score = Score{1920, 1080};
    auto platformController = PlatformController(&log);
    auto platformPositions = platformController.getPlatformPositions(1);
    auto collisionDetector = Collisions(platformController.getPlatformRow(1)->getPlatform(1).width(), 100.0f);
    auto gameSounds = GameSounds();
    player.jack.setPosition(platformPositions.back(), 450); //set Jack on top of a platform
    player.gameRow = 2;
    collisionDetector.update(player, &jack_spritesheet, platformController, &tentText, &tentText, tent, score, gameSounds);
    CHECK(player.score > prevScore);
}

TEST_CASE("Score increases when player wins the game and the temperature is below 50 degrees celsius")
{
    sf::Texture jack_spritesheet, tentText;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    auto temperature = Temperature{1920, 1080};
    auto score = Score{1920, 1080};
    float deltaTime = 10;
    temperature.update(player, &jack_spritesheet, deltaTime);
    auto prevScore = player.score;
    score.updateFromTemp(player, temperature);
    CHECK(player.score > prevScore);
}

TEST_CASE("Score increases when the player collides with a fish")
{
    sf::Texture jack_spritesheet, fishText;
    jack_spritesheet.loadFromFile("resources/jack_frames.png");
    auto player = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 500.0f);
    auto prevScore = player.score;
    fishText.loadFromFile("resources/Fish.png");
    auto numFish = 1;
    auto fishRow = FishController(&fishText, numFish, 50.0f);
    auto score = Score{1920, 1080};
    auto gameSounds = GameSounds{};
    auto fishPos = fishRow.fishPositions().at(0);
    player.jack.setPosition(fishPos, 180*fishRow.row()-90);
    player.gameRow = fishRow.row();
    auto pointCollisions = PointCollisions(fishRow.getFish(1).width());
    pointCollisions.update(player, score, fishRow, gameSounds);
    CHECK(player.score > prevScore);
}
