#include "EnemyCollisions.h"

using namespace std;

EnemyCollisions::EnemyCollisions(float enemyWidth, float enemySpeed)
{
    this->enemyWidth = enemyWidth;
    this->enemySpeed = enemySpeed;
}

void EnemyCollisions::update(Jack& player, sf::Texture* deathTexture, EnemyController& enemies)
{
    for(int i = 0; i < 4; i++)
    {
        auto enemyRow = enemies.getEnemyRow(i+1);
    }

    unsigned int row = player.row();

    if(row > 1)
    {
        if((player.getPositionX() <= 0.0f) || (player.getPositionX() >= 1920))
        {
            player.die(deathTexture);
            return;
        }
        auto xPositions = enemies.getEnemyPositions(row-1);
        bool onEnemy = false;
        for(auto xPos : xPositions)
        {
            if(!player.jumping() && (player.getPositionX()+player.width()/5.0f >= xPos-enemyWidth/2.0f) && (player.getPositionX()-player.width()/5.0f <= xPos+enemyWidth/2.0f)) //player is in bounds of a enemy
            {
                onEnemy = true;
                player.addVelocityX(enemySpeed, enemies.getEnemyRow(row-1)->movingRight);
            }
        }
        if(!onEnemy && !player.jumping())
        {
            player.die(deathTexture);
        }
    }
}
