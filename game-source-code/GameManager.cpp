#include "GameManager.h"

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
    //shared_ptr<sf::SoundBuffer> jumpSound, landSound, victorySound, gameOverSound;
    if(!jumpSoundBuf->loadFromFile("resources/quick-jump.wav") || !landSoundBuf->loadFromFile("resources/landing.wav") || !victorySoundBuf->loadFromFile("resources/completion-of-a-level.wav") || !gameOverSoundBuf->loadFromFile("resources/ominous-drums.wav"))
        throw "cannot load sound";
    gameSounds = GameSounds{*jumpSoundBuf, *landSoundBuf, *victorySoundBuf, *gameOverSoundBuf};

    //Player
    //shared_ptr<sf::Texture> jack_spritesheet, dead_jack, burnt_jack;
    if(!jackSpritesheetText->loadFromFile("resources/jack_frames.png") || !deadJackText->loadFromFile("resources/dead_jack.png") || !burntJackText->loadFromFile("resources/burnt_jack.png"))
        throw "cannot load textures";
    auto player_1 = Jack(jackSpritesheetText.get(), sf::Vector2u(3, 3), 0.2f, 600.0f);
    players.push_back(player_1);

    //Platforms
    //shared_ptr<sf::Texture> log;
    if(!logText->loadFromFile("resources/wide_log.png") || !whiteLogText->loadFromFile("resources/wide_log_white.png"))
        throw "cannot load textures";
    platforms = PlatformController(logText.get());

    //Tent
    //shared_ptr<sf::Texture> tent_spritesheet;
    if(!tentSpritesheetText->loadFromFile("resources/tent.png"))
        throw "cannot load texture";
    tent = Tent{tentSpritesheetText.get(), 4, 4, 200.0f};

    //Collisions
    collisionDetector = Collisions(platforms.getPlatformRow(1)->getPlatform(1).width(), 150.0f);

    //Game State
    isPlaying = false;
    gameOver = false;
    victory = false;
    deltaTime= 0.0f;
}

void GameManager::run()
{
    while(window.isOpen())
    {
        pollEvents();
        update();
        render();
    }
}

void GameManager::pollEvents()
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
            //if(victory)
            //    victorySound.play();
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
            temperature.update(players.at(0), burntJackText.get(), deltaTime);
            collisionDetector.update(players.at(0), deadJackText.get(), platforms, logText.get(), whiteLogText.get(), tent);
            gameSounds.play(players.at(0));
        }
        else
        {
            isPlaying = false;
            gameOver = true;
            //gameOverSound.play();
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
        platforms.draw(window);
        temperature.draw(window);
        players.at(0).draw(window);
    }
    else if(gameOver)
    {
        playingMusic.stop();
        playingRenderer.renderPlayingField(window);
        tent.draw(window);
        platforms.draw(window);
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
