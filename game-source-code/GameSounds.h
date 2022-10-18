#ifndef GAMESOUNDS_H
#define GAMESOUNDS_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Jack.h"

/*!
Responsible for playing all sounds within the game. All public member functions (with the exception of 'void play(Jack& player)')
do not take any paramters as they are only called to play the specified sound.
*/

class GameSounds
{
    public:
        GameSounds(sf::SoundBuffer& jumpSoundBuf, sf::SoundBuffer& landingSoundBuf, sf::SoundBuffer& victorySoundBuf, sf::SoundBuffer& gameOverSoundBuf, sf::SoundBuffer& fishSoundBuf, sf::SoundBuffer& tempScoreSoundBuf);
        GameSounds(){};
        void play(Jack& player); /*!< Plays the respective sound for if the player is jumping or landing by taking in a
                                      reference to the player. */
        void playVictorySound() { victorySound.play(); }
        void playGameOverSound() { gameOverSound.play(); }
        void playFishCollection() { fishSound.play(); }
        void playTempScoreIncreaseing() { tempScoreSound.play(); }

    private:
        sf::Sound jumpSound;
        sf::Sound landingSound;
        sf::Sound victorySound;
        sf::Sound gameOverSound;
        sf::Sound fishSound;
        sf::Sound tempScoreSound;
};

#endif // GAMESOUNDS_H
