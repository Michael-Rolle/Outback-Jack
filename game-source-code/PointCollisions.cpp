#include "PointCollisions.h"

using namespace std;

PointCollisions::PointCollisions(float fishWidth)
{
    this->fishWidth = fishWidth;
}

void PointCollisions::update(Jack& player, Score& score, FishController& fishRow, GameSounds& gameSounds)
{
    if(player.row() == fishRow.row())
    {
        auto xPositions = fishRow.fishPositions();
        unsigned int i = 0;
        for(auto xPos : xPositions)
        {
            i++;
            if(!player.jumping() && (abs(player.getPositionX()-xPos) <= fishWidth/2.0f))
            {
                score.update(player);
                fishRow.removeFish(i);
                gameSounds.playFishCollection();
            }
        }
    }
}
