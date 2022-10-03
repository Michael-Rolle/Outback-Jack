#ifndef GAMESOUNDS_H
#define GAMESOUNDS_H
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Jack.h"


class GameSounds
{
    public:
        GameSounds(sf::SoundBuffer& jumpSoundBuf, sf::SoundBuffer& landingSoundBuf, sf::SoundBuffer& victorySoundBuf, sf::SoundBuffer& gameOverSoundBuf);
        GameSounds(){};
        void play(Jack& player);

    private:
        sf::Sound jumpSound;
        sf::Sound landingSound;
        sf::Sound victorySound;
        sf::Sound gameOverSound;
};

#endif // GAMESOUNDS_H
