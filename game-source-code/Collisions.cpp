#include "Collisions.h"

Collisions::Collisions(Jack& player, PlatformController& platforms)
{
    this->player = player;
    this->platforms = platforms;
}

void Collisions::update()
{
    unsigned int row = player.row();
    if(row > 1)
    {
        auto xPositions = platforms.getPlatformPositions(row-2);
        if(!player.isJumping() && player.getPositionX()+player.width()/2.0f)
    }
}
