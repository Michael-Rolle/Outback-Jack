#include "EnemyCollisions.h"

using namespace std;

EnemyCollisions::EnemyCollisions(float enemyWidth, float enemySpeed)
{
    this->enemyWidth = enemyWidth;
    this->enemySpeed = enemySpeed;
}

void EnemyCollisions::update(Jack& player, sf::Texture* deathTexture, EnemyController& enemies, Kangaroo& kangaroo)
{
    unsigned int row = player.row();

    if(row == 1) //in safe zone
    {
        if(!player.jumping() && abs(player.getPositionX()-kangaroo.getPositionX()) <= (player.width()+kangaroo.width())/2.0f)
            player.die(deathTexture);
    }
    else
    {
        auto xPositions = enemies.getEnemyPositions(row-1);
        for(auto xPos : xPositions)
        {
            if(!player.jumping() && (abs(player.getPositionX()-xPos) <= enemyWidth/2.0f))
            {
                player.die(deathTexture);
            }
        }
    }
}
