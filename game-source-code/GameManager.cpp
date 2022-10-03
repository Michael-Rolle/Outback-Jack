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
    if(!jumpSound->loadFromFile("resources/quick-jump.wav") || !landSound->loadFromFile("resources/landing.wav") || !victorySound->loadFromFile("resources/completion-of-a-level.wav") || !gameOverSound->loadFromFile("resources/ominous-drums.wav"))
        throw "cannot load sound";
    gameSounds = GameSounds{*jumpSound, *landSound, *victorySound, *gameOverSound};

    //Player
    //shared_ptr<sf::Texture> jack_spritesheet, dead_jack, burnt_jack;
    if(!jack_spritesheet->loadFromFile("resources/jack_frames.png") || !dead_jack->loadFromFile("resources/dead_jack.png") || !burnt_jack->loadFromFile("resources/burnt_jack.png"))
        throw "cannot load textures";
    auto player_1 = Jack(jack_spritesheet.get(), sf::Vector2u(3, 3), 0.2f, 600.0f);
    players.push_back(player_1);

    //Platforms
    //shared_ptr<sf::Texture> log;
    if(!log->loadFromFile("resources/wide_log.png") || !white_log->loadFromFile("resources/wide_log_white.png"))
        throw "cannot load textures";
    platforms = PlatformController(log.get());

    //Tent
    //shared_ptr<sf::Texture> tent_spritesheet;
    if(!tent_spritesheet->loadFromFile("resources/tent.png"))
        throw "cannot load texture";
    tent = Tent{tent_spritesheet.get(), 4, 4, 200.0f};

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
            if(victory)
                victorySound.play();
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
            temperature.update(players.at(0), &burnt_jack, deltaTime);
            collisionDetector.update(players.at(0), &dead_jack, platforms, &log, &white_log, tent);
            gameSounds.play(players.at(0));
        }
        else
        {
            isPlaying = false;
            gameOver = true;
            gameOverSound.play();
        }
    }
}

void GameManager::render()
{

}
