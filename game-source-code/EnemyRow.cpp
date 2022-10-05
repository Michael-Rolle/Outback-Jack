#include "EnemyRow.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemy.h"

using namespace std;

EnemyRow::EnemyRow(sf::Texture* texture, const unsigned int numEnemies, const float spacing, const unsigned int gameRow, const bool movingRight, float pos)
{
    this->numEnemies = numEnemies;
    this->spacing = spacing;
    this->gameRow = gameRow;
    this->movingRight = movingRight;
    for(int i = 0; i < (int)numEnemies; i++)
    {
        auto enemy = Enemy{texture, 200.0f, movingRight, gameRow};
        if(movingRight) //ensure the first element in the vector is the left most element
            enemy.setPositionX(pos - ((numEnemies-1-i)*(spacing+enemy.width())+enemy.width()/2.0f));
        else
            enemy.setPositionX(pos + enemy.width()/2.0f + i*(spacing+enemy.width()));
        enemies.push_back(enemy);
    }
}

vector<float> EnemyRow::enemyPositions()
{
    vector<float> positions;
    for(auto& enemy : enemies)
    {
        positions.push_back(enemy.getPositionX());
    }
    return positions;
}

void EnemyRow::changeDirection()
{
    movingRight = !movingRight;
    for(auto& enemy : enemies)
        enemy.changeDirection();
}

void EnemyRow::update(float deltaTime)
{
    for(auto& enemy : enemies)
    {
        if(enemy.getPositionX()+enemy.width()/2.0f <= 0 && !movingRight)
            enemy.setPositionX(1920+enemy.width()/2.0f);
        else if(enemy.getPositionX()-enemy.width()/2.0f >= 1920 && movingRight)
            enemy.setPositionX(0-enemy.width()/2.0f);

        enemy.update(deltaTime);
    }
}

void EnemyRow::draw(sf::RenderWindow& window)
{
    for(auto& enemy : enemies)
        enemy.draw(window);
}
