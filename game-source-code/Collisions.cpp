#include "Collisions.h"

using namespace std;

Collisions::Collisions(float platformWidth, float platformSpeed)
{
    this->platformWidth = platformWidth;
    this->platformSpeed = platformSpeed;
}

void Collisions::update(Jack& player, sf::Texture* deathTexture, PlatformController& platforms, sf::Texture* originalColour, sf::Texture* newColour, Tent& tent, Score& score, GameSounds& gameSounds)
{
    if(tent.built)
    {
        for(int i = 0; i < 4; i++)
        {
            auto platformRow = platforms.getPlatformRow(i+1);
            platformRow->changeColour(newColour, false);
            platformRow->canChangeColour = false;
        }
    }
    unsigned int row = player.row();
    if(row > 1)
    {
        if((player.getPositionX() <= 0.0f) || (player.getPositionX() >= 1920))
        {
            player.die(deathTexture);
            return;
        }
        auto xPositions = platforms.getPlatformPositions(row-1);
        bool onPlatform = false;
        for(auto xPos : xPositions)
        {
            if(!player.jumping() && (player.getPositionX()+player.width()/5.0f >= xPos-platformWidth/2.0f) && (player.getPositionX()-player.width()/5.0f <= xPos+platformWidth/2.0f)) //player is in bounds of a log
            {
                onPlatform = true;
                player.addVelocityX(platformSpeed, platforms.getPlatformRow(row-1)->movingRight);
                if(platforms.getPlatformRow(row-1)->isOriginalColour && platforms.getPlatformRow(row-1)->canChangeColour)
                {
                    platforms.changePlatformRowColour(row-1, newColour, false);
                    gameSounds.playLandingSound();
                    score.update(player);
                    tent.nextFrame();
                    if(platforms.allPlatformsNewColour())
                        platforms.getPlatformRow(row-1)->canChangeColour = false;
                }
            }
            else if(player.jumping() && platforms.allPlatformsNewColour() && !tent.built)
            {
                for(int i = 0; i < 4; i++)
                {
                    platforms.changePlatformRowColour(i+1, originalColour, true);
                    platforms.getPlatformRow(i+1)->canChangeColour = true;
                }
                return;
            }
        }
        if(!onPlatform && !player.jumping())
        {
            player.die(deathTexture);
        }
    }
}
