#include "GameManager.h"

GameManager::GameManager(bool twoPlayer_):
    twoPlayer{twoPlayer_},
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
    shared_ptr<sf::SoundBuffer> jump, land, victory, gameOver;
    if(!jump->loadFromFile("resources/quick-jump.wav") || !land->loadFromFile("resources/landing.wav") || !victory->loadFromFile("resources/completion-of-a-level.wav") || !gameOver->loadFromFile("resources/ominous-drums.wav"))
        throw "cannot load sound";
    gameSounds = GameSounds{*jump, *land, *victory, *gameOver};

    //Jack Textures
    shared_ptr<sf::Texture> jack_spritesheet, dead_jack, burnt_jack;
    if(!jack_spritesheet->loadFromFile("resources/jack_frames.png") || !dead_jack->loadFromFile("resources/dead_jack.png") || !burnt_jack->loadFromFile("resources/burnt_jack.png"))
        throw "cannot load textures";
    if(!twoPlayer)
    {
        auto player_1 = Jack(jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 600.0f);
        players.push_back(player_1);
    }

    //Platforms
    shared_ptr<sf::Texture> log;
    if(!log->loadFromFile("resources/wide_log.png"))
        throw "cannot load texture";
    platforms = PlatformController(log);

    //Tent
    shared_ptr<sf::Texture> tent_spritesheet;
    if(!tent_spritesheet->loadFromFile("resources/tent.png"))
        throw "cannot load texture";
    tent = Tent{tent_spritesheet, 4, 4};

    //Collisions
    collisionDetector = Collisions(platforms.getPlatformRow(1)->getPlatform(1).width(), 150.0f);

    //Game State
    isPlaying = false;
    gameOver = false;
    victory = false;
}
