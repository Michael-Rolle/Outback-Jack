#include "GameSounds.h"

GameSounds::GameSounds(sf::SoundBuffer& jumpSoundBuf, sf::SoundBuffer& landingSoundBuf, sf::SoundBuffer& victorySoundBuf, sf::SoundBuffer& gameOverSoundBuf, sf::SoundBuffer& fishSoundBuf)
{
    jumpSound.setBuffer(jumpSoundBuf);
    landingSound.setBuffer(landingSoundBuf);
    victorySound.setBuffer(victorySoundBuf);
    gameOverSound.setBuffer(gameOverSoundBuf);
    fishSound.setBuffer(fishSoundBuf);
}

void GameSounds::play(Jack& player)
{
    if(player.playJumpSound)
        jumpSound.play();
    if(player.playLandingSound)
        landingSound.play();
}
