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
#include "Kangaroo.h"
#include "PlatformController.h"
#include "Collisions.h"
#include "Enemy.h"
#include "EnemyCollisions.h"
#include "EnemyController.h"
#include "Temperature.h"
#include "Score.h"
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
        sf::Texture kangarooSpritesheetText;
        Kangaroo kangaroo;
        PlatformController platforms;
        Collisions collisionDetector;
        sf::Texture crocText;
        EnemyController enemies;
        EnemyCollisions enemyCollisionDetector;
        Temperature temperature;
        Score score;
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
