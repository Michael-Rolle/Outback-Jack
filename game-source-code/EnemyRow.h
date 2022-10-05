#ifndef ENEMYROW_H
#define ENEMYROW_H
#include "Enemy.h"
#include <vector>

//using namespace std;
using std::vector;

class EnemyRow
{
    public:
        EnemyRow(sf::Texture* texture, const unsigned int numEnemies, const float spacing, const unsigned int gameRow, const bool movingRight, float pos);
        ~EnemyRow(){}
        vector<float> enemyPositions();
        Enemy getEnemy(const unsigned int enemyNum){ return enemies.at(enemyNum-1); } //enter a number from 1 to numEnemies
        void update(float deltaTime);
        void draw(sf::RenderWindow& window);

    public:
        bool movingRight;
    private:
        vector<Enemy> enemies;
        unsigned int gameRow;
        float spacing;
        unsigned int numEnemies;
        float pos;
};

#endif // ENEMYROW_H
