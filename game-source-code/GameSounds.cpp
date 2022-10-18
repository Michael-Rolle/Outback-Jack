#include "GameSounds.h"

GameSounds::GameSounds(sf::SoundBuffer& jumpSoundBuf, sf::SoundBuffer& landingSoundBuf, sf::SoundBuffer& victorySoundBuf, sf::SoundBuffer& gameOverSoundBuf, sf::SoundBuffer& fishSoundBuf, sf::SoundBuffer& tempScoreSoundBuf)
{
    jumpSound.setBuffer(jumpSoundBuf);
    landingSound.setBuffer(landingSoundBuf);
    victorySound.setBuffer(victorySoundBuf);
    gameOverSound.setBuffer(gameOverSoundBuf);
    fishSound.setBuffer(fishSoundBuf);
    tempScoreSound.setBuffer(tempScoreSoundBuf);
    jumpSound.setVolume(30);
    landingSound.setVolume(30);
    victorySound.setVolume(30);
    gameOverSound.setVolume(30);
    fishSound.setVolume(10);
    tempScoreSound.setVolume(10);
}

/*void GameSounds::play(Jack& player)
{
    if(player.playJumpSound)
        jumpSound.play();
    if(player.playLandingSound)
        landingSound.play();
}*/
