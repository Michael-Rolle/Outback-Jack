#include "Collisions.h"

Collisions::Collisions(Jack& player, PlatformController& platforms, float platformWidth, float platformSpeed)
{
    this->player = player;
    this->platforms = platforms;
    this->platformWidth = platformWidth;
    this->platformSpeed = platformSpeed;
}

void Collisions::update()
{
    unsigned int row = player.row();
    if(row > 1)
    {
        auto xPositions = platforms.getPlatformPositions(row-2);
        for(auto xPos : xPositions)
        {
            if(!player.jumping() && player.getPositionX() >= xPos-platformWidth/2.0f && player.getPositionX() <= xPos+platformWidth/2.0f)
                player.addVelocityX(platformSpeed, platforms.getPlatformRow(row-2).movingRight());
        }
    }
}
