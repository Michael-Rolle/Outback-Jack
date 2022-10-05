#include "PointCollisions.h"

using namespace std;

PointCollisions::PointCollisions(float fishWidth)
{
    this->fishWidth = fishWidth;
    //this->enemySpeed = enemySpeed;
}

/*void PointCollisions::update(Jack& player, Score& score, EnemyController& friends)
{
    unsigned int row = player.row();

    if(row == 2 || row == 3 || row == 4 || row == 5)
    {
        auto xPositions = friends.getEnemyPositions(row-1);
        for(auto xPos : xPositions)
        {
            if(!player.jumping() && (abs(player.getPositionX()-xPos) <= enemyWidth/2.0f))
            {
                score.update();
            }
        }
    }
}*/

void PointCollisions::update(Jack& player, Score& score, FishController& fishRow)
{
    //unsigned int row = player.row();

    if(player.row() == fishRow.row())
    {
        auto xPositions = fishRow.fishPositions();
        unsigned int i = 0;
        for(auto xPos : xPositions)
        {
            i++;
            if(!player.jumping() && (abs(player.getPositionX()-xPos) <= fishWidth/2.0f))
            {
                score.update();
                fishRow.removeFish(i);
            }
        }
    }
}
