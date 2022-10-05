#include "PointCollisions.h"

using namespace std;

PointCollisions::PointCollisions(float enemyWidth, float enemySpeed)
{
    this->enemyWidth = enemyWidth;
    this->enemySpeed = enemySpeed;
}

void PointCollisions::update(Jack& player, Score& score, EnemyController& friends)
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
}
