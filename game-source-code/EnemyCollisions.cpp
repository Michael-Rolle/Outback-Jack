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

    if(row == 1)
    {
        if(abs(player.getPositionX()-kangaroo.getPositionX()) <= (player.width()+kangaroo.width())/2.0f)
            player.die(deathTexture);
    }
    if(row > 1)
    {
        auto xPositions = enemies.getEnemyPositions(row-1);
        bool onEnemy = false;
        for(auto xPos : xPositions)
        {
            if(!player.jumping() && (player.getPositionX()+player.width()/5.0f >= xPos-enemyWidth/2.0f) && (player.getPositionX()-player.width()/5.0f <= xPos+enemyWidth/2.0f)) //player is in bounds of a enemy
            {
                onEnemy = true;
            }
        }
        if(onEnemy && !player.jumping())
        {
            player.die(deathTexture);
        }
    }
}
