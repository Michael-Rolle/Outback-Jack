#include "Collisions.h"

Collisions::Collisions(float platformWidth, float platformSpeed)
{
    this->platformWidth = platformWidth;
    this->platformSpeed = platformSpeed;
}

void Collisions::update(Jack& player, PlatformController& platforms, sf::Texture* originalColour, sf::Texture* newColour)
{
    unsigned int row = player.row();
    if(row > 1)
    {
        auto xPositions = platforms.getPlatformPositions(row-1);
        for(auto xPos : xPositions)
        {
            if(!player.jumping() && (player.getPositionX() >= xPos-platformWidth/2.0f) && (player.getPositionX() <= xPos+platformWidth/2.0f)) //player is in bounds of a log
            {
                player.addVelocityX(platformSpeed, platforms.getPlatformRow(row-1)->movingRight);
                if(platforms.getPlatformRow(row-1)->isOriginalColour && platforms.getPlatformRow(row-1)->canChangeColour)
                {
                    platforms.changePlatformRowColour(row-1, newColour, false);
                    if(platforms.allPlatformsNewColour())
                        platforms.getPlatformRow(row-1)->canChangeColour = false;
                }
            }
            else if(player.jumping() && platforms.allPlatformsNewColour())
            {
                for(int i = 0; i < 4; i++)
                {
                    platforms.changePlatformRowColour(i+1, originalColour, true);
                    platforms.getPlatformRow(i+1)->canChangeColour = true;
                }
            }
        }
    }
}