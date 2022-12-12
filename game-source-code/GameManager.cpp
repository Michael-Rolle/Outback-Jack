#include "GameManager.h"
#include <vector>

using namespace std;

//Constructor intializes all variables
GameManager::GameManager():
    window{sf::VideoMode(1280, 720), "Outback Jack"},
    splashRenderer{gameWidth, gameHeight},
    playingRenderer{gameWidth, gameHeight},
    //victoryRenderer{gameWidth, gameHeight},
    //defeatRenderer{gameWidth, gameHeight},
    endScreenRenderer(gameWidth, gameHeight),
    temperature{gameWidth, gameHeight},
    score{gameWidth, gameHeight}
{
    //Window
    window.setView(sf::View(sf::FloatRect(0.0f, 0.0f, gameWidth, gameHeight)));
    window.setFramerateLimit(frameRate);

    //Music
    if(!splashMusic.openFromFile("resources/18 The Archives.wav"))
        throw "cannot load music file";
    splashMusic.setLoop(true);
    splashMusic.setVolume(10);
    splashMusic.play();
    if(!playingMusic.openFromFile("resources/05 Den of Thieves.wav"))
        throw "cannot load music file";
    playingMusic.setLoop(true);
    playingMusic.setVolume(10);

    //Game Sounds
    if(!jumpSoundBuf.loadFromFile("resources/quick-jump.wav") || !landSoundBuf.loadFromFile("resources/landing.wav") || !victorySoundBuf.loadFromFile("resources/completion-of-a-level.wav") || !gameOverSoundBuf.loadFromFile("resources/ominous-drums.wav") || !fishSoundBuf.loadFromFile("resources/bonus.wav") || !tempScoreSoundBuf.loadFromFile("resources/score-increasing.wav"))
        throw "cannot load sound";
    gameSounds = GameSounds{jumpSoundBuf, landSoundBuf, victorySoundBuf, gameOverSoundBuf, fishSoundBuf, tempScoreSoundBuf};

    //Player
    if(!jackSpritesheetText.loadFromFile("resources/jack_frames.png") || !deadJackText.loadFromFile("resources/dead_jack.png") || !burntJackText.loadFromFile("resources/burnt_jack.png"))
        throw "cannot load textures";
    if(!jackSpritesheetTextRed.loadFromFile("resources/jack_frames_red.png") || !deadJackTextRed.loadFromFile("resources/dead_jack_red.png") || !burntJackTextRed.loadFromFile("resources/burnt_jack_red.png"))
        throw "cannot load textures";
    auto player_1 = Jack(&jackSpritesheetText, sf::Vector2u(3, 3), 0.2f, 600.0f, 1);
    auto player_2 = Jack(&jackSpritesheetTextRed, sf::Vector2u(3, 3), 0.2f, 600.0f, 2);
    players.push_back(player_1);
    players.push_back(player_2);

    //Enemies
    if(!crocText.loadFromFile("resources/croc.png"))
    {
       throw "cannot load texture";
    }
    enemies = EnemyController(&crocText, 1920);

    //Points
    if(!fishText.loadFromFile("resources/Fish.png"))
    {
       throw "cannot load texture";
    }
    fishRow = FishController(&fishText, 3, 50.0f);

    //Kangaroo
    if(!kangarooSpritesheetText.loadFromFile("resources/kangaroo.png"))
        throw "cannot load texture";
    kangaroo = Kangaroo{&kangarooSpritesheetText, sf::Vector2u{3,1}, 0.3f, 200.0f};

    //Platforms
    if(!logText.loadFromFile("resources/wide_log.png") || !whiteLogText.loadFromFile("resources/wide_log_white.png"))
        throw "cannot load textures";
    platforms = PlatformController(&logText);

    //Tent
    if(!tentSpritesheetText.loadFromFile("resources/tent.png"))
        throw "cannot load texture";
    tents.push_back(Tent{&tentSpritesheetText, 4, 4, 200.0f, 0.25*1920.0f});
    tents.push_back(Tent{&tentSpritesheetText, 4, 4, 200.0f, 0.75*1920.0f});

    //Collisions
    collisionDetector = Collisions(platforms.getPlatformRow(1)->getPlatform(1).width(), 150.0f);
    enemyCollisionDetector = EnemyCollisions(enemies.getEnemyRow(1)->getEnemy(1).width(), 150.0f);
    pointCollisionDetector = PointCollisions(fishRow.getFish(1).width());

    //Game State
    isPlaying = false;
    gameOver = false;
    victory = false;
    deltaTime= 0.0f;
}

//Main game loop
void GameManager::run()
{
    while(window.isOpen())
    {
        pollEvent();
        update();
        render();
    }
}

void GameManager::pollEvent()
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
            splashMusic.stop();
            playingMusic.play();
            clock.restart();
        }

        if(isPlaying && !victory)
        {
            for(auto& player: players)
                player.setMovement(event, gameSounds);
            victory = (players.at(0).wonGame(event, tents.at(0), PlayerNumber::One) || players.at(1).wonGame(event, tents.at(1), PlayerNumber::Two));
            if(victory)
            {
               gameSounds.playTempScoreIncreaseing();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && players.at(0).row() > 1)
            {
                platforms.getPlatformRow(players.at(0).row()-1)->changeDirection();
                tents.at(0).removeFrame();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) && players.at(1).row() > 1)
            {
                platforms.getPlatformRow(players.at(1).row()-1)->changeDirection();
                tents.at(1).removeFrame();
            }
        }

        if((gameOver || victory) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            resetGame();
        }
    }
}

void GameManager::update()
{
    if(isPlaying && !victory)
    {
        if(players.at(0).isAlive && players.at(1).isAlive)
        {
            deltaTime = clock.restart().asSeconds();
            platforms.update(deltaTime);
            enemies.update(deltaTime);
            fishRow.update(deltaTime);
            kangaroo.update(players, deltaTime);
            int count = 0;
            for(auto& player: players)
            {
                player.update(deltaTime);
                if(player.playerNum == 1)
                {
                    temperature.update(player, &burntJackText, deltaTime);
                    collisionDetector.update(player, &deadJackText, platforms, &logText, &whiteLogText, tents.at(0), score, gameSounds);
                    enemyCollisionDetector.update(player, &deadJackText, enemies, kangaroo);
                }
                else
                {
                    temperature.update(player, &burntJackTextRed, deltaTime);
                    collisionDetector.update(player, &deadJackTextRed, platforms, &logText, &whiteLogText, tents.at(1), score, gameSounds);
                    enemyCollisionDetector.update(player, &deadJackTextRed, enemies, kangaroo);
                }
                pointCollisionDetector.update(player, score, fishRow, gameSounds);
                count += 1;
            }
        }
        else
        {
            isPlaying = false;
            gameOver = true;
            gameSounds.playGameOverSound();
            if(players.at(0).isAlive)
                endScreenRenderer.displayWin(PlayerNumber::One);
            else if(players.at(1).isAlive)
                endScreenRenderer.displayWin(PlayerNumber::Two);
        }
    }
    else if(victory)
    {
        if(players.at(0).victory)
        {
            score.updateFromTemp(players.at(0), temperature);
            endScreenRenderer.displayWin(PlayerNumber::One);
        }
        else if(players.at(1).victory)
        {
            score.updateFromTemp(players.at(1), temperature);
            endScreenRenderer.displayWin(PlayerNumber::Two);
        }
    }
}

void GameManager::render()
{
    window.clear();
    if(isPlaying || gameOver || victory)
    {
        playingRenderer.draw(window);
        for(auto& tent: tents)
            tent.draw(window);
        platforms.draw(window);
        fishRow.draw(window);
        enemies.draw(window);
        kangaroo.draw(window);
        for(auto& player: players)
            player.draw(window);
        temperature.draw(window);
        score.draw(window);
        if(gameOver)
        {
            playingMusic.stop();
            //defeatRenderer.draw(window);
            endScreenRenderer.draw(window);
        }
        else if(victory)
        {
            playingMusic.stop();
            //victoryRenderer.draw(window);
            endScreenRenderer.draw(window);
        }
    }
    else
    {
        //draw the splash screen
        splashRenderer.draw(window);
    }
    window.display();
}

void GameManager::resetGame()
{
    auto num = 1;
    for(auto& player : players)
    {
        if(num == 1)
            player = Jack{&jackSpritesheetText, sf::Vector2u(3, 3), 0.2f, 600.0f, num};
        else
            player = Jack{&jackSpritesheetTextRed, sf::Vector2u(3, 3), 0.2f, 600.0f, num};
        num += 1;
    }
    kangaroo = Kangaroo(&kangarooSpritesheetText, sf::Vector2u{3,1}, 0.3f, 200.0f);
    platforms = PlatformController(&logText);
    enemies = EnemyController(&crocText, 1920);
    fishRow = FishController(&fishText, 3, 50.0f);
    for(auto& tent: tents)
        tent.reset();
    temperature.reset();
    score.reset();

    isPlaying = true;
    gameOver = false;
    victory = false;
    deltaTime= 0.0f;
    clock.restart().asSeconds();
    playingMusic.play();
}
