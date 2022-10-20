#ifndef ENEMYROW_H
#define ENEMYROW_H
#include "Enemy.h"
#include <vector>

/*!
Creates a row of enemies capable of being moved and updated as one unit.
*/

using std::vector;

class EnemyRow
{
    public:
        EnemyRow(sf::Texture* texture, const unsigned int numEnemies, const float spacing, const unsigned int gameRow, const bool movingRight, float pos);
        ~EnemyRow(){}
        vector<float> enemyPositions();
        /*!< Returns a vector of floats containing the positions of all enemies within the row. */
        Enemy getEnemy(const unsigned int enemyNum){ return enemies.at(enemyNum-1); }
        /*!< Returns the Enemy object within the enemies vector, respective to the parameter. Number of the enemy is always a positive integer. */
        void update(float deltaTime);
        /*!< Updates the positions of all enemies within the EnemyRow respective to the input float. */
        void draw(sf::RenderWindow& window);
        /*!< Draws each enemy within the EnemyRow with reference to a RenderWindow. */

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
