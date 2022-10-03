// Headers
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "SplashScreenRenderer.h"
#include "PlayingFieldRenderer.h"
#include "VictoryScreenRenderer.h"
#include "Jack.h"
#include "PlatformController.h"
#include "Collisions.h"
#include "Enemy.h"
#include "Temperature.h"
#include "Tent.h"
#include "GameSounds.h"
#include <cstdlib>
#include <iostream>

using namespace std;

// Global Constants
const float gameWidth = 1920;
const float gameHeight = 1080;
const unsigned short frameRate = 60;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Outback Jack");
    window.setView(sf::View(sf::FloatRect(0.0f, 0.0f, gameWidth, gameHeight)));
    window.setFramerateLimit(frameRate);

    // Initialize the splash screen, playing field, Jack, tent, and platforms
    sf::Font font;
    if(!font.loadFromFile("resources/I-Have-Bad-News.ttf"))
        return EXIT_FAILURE;
    auto splashRenderer = SplashScreenRenderer(gameWidth, gameHeight);
    auto playingFieldRenderer = PlayingFieldRenderer(gameWidth, gameHeight);
    auto victoryScreenRenderer = VictoryScreenRenderer(&font);

    sf::Music splashMusic;
    if(!splashMusic.openFromFile("resources/18 The Archives.wav"))
        throw "cannot load music file";
    splashMusic.setLoop(true);
    splashMusic.setVolume(10);
    splashMusic.play();

    sf::Music playingMusic;
    if(!playingMusic.openFromFile("resources/05 Den of Thieves.wav"))
        throw "cannot load music file";
    playingMusic.setLoop(true);
    playingMusic.setVolume(10);

    //Game sounds
    sf::SoundBuffer jumpSoundBuffer;
    sf::SoundBuffer gameOverSoundBuffer;
    sf::SoundBuffer victorySoundBuffer;
    if(!jumpSoundBuffer.loadFromFile("resources/quick-jump.wav") || !gameOverSoundBuffer.loadFromFile("resources/ominous-drums.wav") || !victorySoundBuffer.loadFromFile("resources/completion-of-a-level.wav"))
        return EXIT_FAILURE;
    auto victorySound = sf::Sound{victorySoundBuffer};
    auto gameOverSound = sf::Sound{gameOverSoundBuffer};
    auto gameSounds = GameSounds{jumpSoundBuffer, victorySoundBuffer, gameOverSoundBuffer};

    sf::Texture jack_spritesheet;
    if(!jack_spritesheet.loadFromFile("resources/jack_frames.png"))
        return EXIT_FAILURE;

    sf::Texture dead_jack;
    if(!dead_jack.loadFromFile("resources/dead_jack.png"))
        return EXIT_FAILURE;
    sf::Texture burnt_jack;
    if(!burnt_jack.loadFromFile("resources/burnt_jack.png"))
        return EXIT_FAILURE;

    auto Player_1 = Jack(&jack_spritesheet, sf::Vector2u(3, 3), 0.2f, 600.0f);

    sf::Texture log;
    if(!log.loadFromFile("resources/wide_log.png"))
        return EXIT_FAILURE;
    sf::Texture white_log;
    if(!white_log.loadFromFile("resources/wide_log_white.png"))
        return EXIT_FAILURE;
    auto platforms = PlatformController(&log);

    sf::Texture croc;
    if(!croc.loadFromFile("resources/croc.png"))
        return EXIT_FAILURE;
    auto crocs = Enemy(&croc, 500.0f, true, 1);

    sf::Texture tent_spritesheet;
    if(!tent_spritesheet.loadFromFile("resources/tent.png"))
        return EXIT_FAILURE;
    auto tent = Tent(&tent_spritesheet, 4, 4);

    auto collisionDetector = Collisions(platforms.getPlatformRow(1)->getPlatform(1).width(), 150.0f);

    sf::Clock clock;
    float deltaTime = 0;
    bool isPlaying = false;
    bool gameOver = false;
    bool victory = false;

    auto temperature = Temperature(gameWidth, gameHeight);

    while(window.isOpen())
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
                Player_1.setMovement(event);
                victory = Player_1.wonGame(event, tent);
                if(victory)
                    victorySound.play();
            }
        }

        if(isPlaying && !victory)
        {
            if(Player_1.isAlive)
            {
                deltaTime = clock.restart().asSeconds();
                gameSounds.play(Player_1);
                Player_1.update(deltaTime); //controls movement and animations
                platforms.update(deltaTime);
                temperature.update(Player_1, &burnt_jack, deltaTime);
                collisionDetector.update(Player_1, &dead_jack, platforms, &log, &white_log, tent);
            }
            else
            {
                isPlaying = false;
                gameOver = true;
                gameOverSound.play();
            }
        }

        // Render
        window.clear();
        if(isPlaying && !gameOver && !victory)
        {
            playingFieldRenderer.renderPlayingField(window);
            tent.draw(window);
            crocs.draw(window);
            platforms.draw(window);
            temperature.draw(window);
            Player_1.draw(window);
        }
        else if(gameOver)
        {
            playingMusic.stop();
            playingFieldRenderer.renderPlayingField(window);
            tent.draw(window);
            crocs.draw(window);
            platforms.draw(window);
            temperature.draw(window);
            Player_1.draw(window);
        }
        else if(victory)
        {
            playingMusic.stop();
            tent.draw(window);
            Player_1.draw(window);
            victoryScreenRenderer.draw(window);
        }
        else
        {
            //draw the splash screen
            splashRenderer.renderSplashScreen(window);
        }
        window.display();
    }

    return EXIT_SUCCESS;
}
