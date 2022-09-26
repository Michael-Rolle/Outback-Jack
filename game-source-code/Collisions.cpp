#include "Collisions.h"

Collisions::Collisions(float platformWidth, float platformSpeed)
{
    this->platformWidth = platformWidth;
    this->platformSpeed = platformSpeed;
}

void Collisions::update(Jack& player, PlatformController& platforms)
{
    unsigned int row = player.row();
    if(row > 1)
    {
        auto xPositions = platforms.getPlatformPositions(row-1);
        for(auto xPos : xPositions)
        {
            if(!player.jumping() && (player.getPositionX() >= xPos-platformWidth/2.0f) && (player.getPositionX() <= xPos+platformWidth/2.0f))
                player.addVelocityX(platformSpeed, platforms.getPlatformRow(row-1).isMovingRight());
        }
    }
}
