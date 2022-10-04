#include "GameManager.h"

//Constructor intializes all variables
GameManager::GameManager():
    window{sf::VideoMode(1280, 720), "Outback Jack"},
    splashRenderer{gameWidth, gameHeight},
    playingRenderer{gameWidth, gameHeight},
    victoryRenderer{gameWidth, gameHeight},
    temperature{gameWidth, gameHeight}
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
    if(!jumpSoundBuf.loadFromFile("resources/quick-jump.wav") || !landSoundBuf.loadFromFile("resources/landing.wav") || !victorySoundBuf.loadFromFile("resources/completion-of-a-level.wav") || !gameOverSoundBuf.loadFromFile("resources/ominous-drums.wav"))
        throw "cannot load sound";
    gameSounds = GameSounds{jumpSoundBuf, landSoundBuf, victorySoundBuf, gameOverSoundBuf};

    //Player
    if(!jackSpritesheetText.loadFromFile("resources/jack_frames.png") || !deadJackText.loadFromFile("resources/dead_jack.png") || !burntJackText.loadFromFile("resources/burnt_jack.png"))
        throw "cannot load textures";
    auto player_1 = Jack(&jackSpritesheetText, sf::Vector2u(3, 3), 0.2f, 600.0f);
    players.push_back(player_1);

    //Enemies
    if(!crocText.loadFromFile("resources/croc.png"))
    {
       throw "cannot load texture";
    }
    enemies = EnemyController(&crocText);

    //Kangaroo
    if(!kangarooSpritesheetText.loadFromFile("resources/kangaroo.png"))
        throw "cannot load texture";
    kangaroo = Kangaroo{&kangarooSpritesheetText, sf::Vector2u{3,1}, 0.3f, 300.0f};

    //Platforms
    if(!logText.loadFromFile("resources/wide_log.png") || !whiteLogText.loadFromFile("resources/wide_log_white.png"))
        throw "cannot load textures";
    platforms = PlatformController(&logText);

    //Tent
    if(!tentSpritesheetText.loadFromFile("resources/tent.png"))
        throw "cannot load texture";
    tent = Tent{&tentSpritesheetText, 4, 4, 200.0f};

    //Collisions
    collisionDetector = Collisions(platforms.getPlatformRow(1)->getPlatform(1).width(), 150.0f);
    enemyCollisionDetector = EnemyCollisions(enemies.getEnemyRow(1)->getEnemy(1).width(), 150.0f);

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
            players.at(0).setMovement(event);
            gameSounds.play(players.at(0));
            victory = players.at(0).wonGame(event, tent);
            if(victory)
                gameSounds.playVictorySound();
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
        if(players.at(0).isAlive)
        {
            deltaTime = clock.restart().asSeconds();
            players.at(0).update(deltaTime); //controls movement and animations
            platforms.update(deltaTime);
            enemies.update(deltaTime);
            temperature.update(players.at(0), &burntJackText, deltaTime);
            collisionDetector.update(players.at(0), &deadJackText, platforms, &logText, &whiteLogText, tent);
            enemyCollisionDetector.update(players.at(0), &deadJackText, enemies);
            gameSounds.play(players.at(0));
            kangaroo.update(players.at(0), deltaTime);
        }
        else
        {
            isPlaying = false;
            gameOver = true;
            gameSounds.playGameOverSound();
        }
    }
}

void GameManager::render()
{
    window.clear();
    if(isPlaying && !gameOver && !victory)
    {
        playingRenderer.renderPlayingField(window);
        tent.draw(window);
        kangaroo.draw(window);
        platforms.draw(window);
        enemies.draw(window);
        temperature.draw(window);
        players.at(0).draw(window);
    }
    else if(gameOver)
    {
        playingMusic.stop();
        playingRenderer.renderPlayingField(window);
        tent.draw(window);
        platforms.draw(window);
        //enemies.draw(window);
        temperature.draw(window);
        players.at(0).draw(window);
    }
    else if(victory)
    {
        playingMusic.stop();
        tent.draw(window);
        players.at(0).draw(window);
        victoryRenderer.draw(window);
    }
    else
    {
        //draw the splash screen
        splashRenderer.renderSplashScreen(window);
    }
    window.display();
}

void GameManager::resetGame()
{
    for(auto& player : players)
    {
        player = Jack{&jackSpritesheetText, sf::Vector2u(3, 3), 0.2f, 600.0f};
    }
    platforms = PlatformController(&logText);
    enemies = EnemyController(&crocText);
    tent.reset();
    temperature.reset();

    isPlaying = true;
    gameOver = false;
    victory = false;
    deltaTime= 0.0f;
    clock.restart().asSeconds();
    playingMusic.play();
}
