#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
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

using std::vector;

class GameManager
{
    public:
        GameManager();
        void run();
    private:
        void pollEvent();
        void update();
        void render();
        void resetGame();

    private:
        sf::RenderWindow window;
        const float gameWidth = 1920.0f;
        const float gameHeight = 1080.0f;
        const unsigned short frameRate = 60;
        SplashScreenRenderer splashRenderer;
        PlayingFieldRenderer playingRenderer;
        VictoryScreenRenderer victoryRenderer;
        sf::Music splashMusic;
        sf::Music playingMusic;
        sf::SoundBuffer jumpSoundBuf, landSoundBuf, victorySoundBuf, gameOverSoundBuf;
        GameSounds gameSounds;
        sf::Texture jackSpritesheetText, deadJackText, burntJackText, logText, whiteLogText;
        vector<Jack> players;
        PlatformController platforms;
        Collisions collisionDetector;
        Temperature temperature;
        sf::Texture tentSpritesheetText;
        Tent tent;
        sf::Clock clock;
        float deltaTime;
        bool twoPlayer;
        bool isPlaying;
        bool gameOver;
        bool victory;
};

#endif // GAMEMANAGER_H