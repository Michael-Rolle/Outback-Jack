#include "GameManager.h"

GameManager::GameManager():
    window{sf::VideoMode(1280, 720), "Outback Jack"},
    splashRenderer{gameWidth, gameHeight},
    playingRenderer{gameWidth, gameHeight},
    victoryRenderer{gameWidth, gameHeight}
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
    sf::SoundBuffer jump, land, victory, gameOver;
    if(!jump.loadFromFile("resources/quick-jump.wav") || !land.loadFromFile("resources/landing.wav") || !victory.loadFromFile("resources/completion-of-a-level.wav") || !gameOver.loadFromFile("resources/ominous-drums.wav"))
        throw "cannot load sound";
}
