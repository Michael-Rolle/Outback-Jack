#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "SplashScreenRenderer.h"
#include "PlayingFieldRenderer.h"
#include "VictoryScreenRenderer.h"
#include "DefeatScreenRenderer.h"
#include "Jack.h"
#include "Kangaroo.h"
#include "PlatformController.h"
#include "Collisions.h"
#include "Enemy.h"
#include "EnemyCollisions.h"
#include "PointCollisions.h"
#include "EnemyController.h"
#include "FishController.h"
#include "Temperature.h"
#include "Score.h"
#include "Tent.h"
#include "GameSounds.h"
#include <cstdlib>

using std::vector;

/*! \mainpage
All public member functions specified as 'void' do not return a type as they are manipulative functions about their object. Data is then incapable of being read from these functions. If one
of these function does not accept any parameter it is usually a 'Setter' or 'Getter' type function.

All other functions return a type as these types and their respective data are required for other implementations.
*/

/*!
Class responsible for the creation of the game window and the creation and visualisation of all game objects. It updates the state of the game while polling for events, until the game has
ended. The game can then be reset.
*/

class GameManager
{
    public:
        GameManager();
        void run();
        /*!< Takes in no parameters and doesn't return a type. Responsible for executing private member functions while the window is open. Hence updating the game as events take place. */
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
        DefeatScreenRenderer defeatRenderer;
        sf::Music splashMusic;
        sf::Music playingMusic;
        sf::SoundBuffer jumpSoundBuf, landSoundBuf, victorySoundBuf, gameOverSoundBuf, fishSoundBuf, tempScoreSoundBuf;
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
        sf::Texture fishText;
        FishController fishRow;
        PointCollisions pointCollisionDetector;
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
