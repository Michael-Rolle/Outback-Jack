#ifndef ENEMYROW_H
#define ENEMYROW_H
#include "Enemy.h"
#include <vector>

using namespace std;

class EnemyRow
{
    public:
        EnemyRow(sf::Texture* texture, const unsigned int numEnemies, const float spacing, const unsigned int gameRow, const bool movingRight);
        ~EnemyRow(){}
        vector<float> platformPositions();
        Platform getPlatform(const unsigned int platformNum){ return platforms.at(platformNum-1); } //enter a number from 1 to numEnemies
        void changeDirection();
        //void changeColour(sf::Texture* texture, bool original);
        void update(float deltaTime);
        void draw(sf::RenderWindow& window);

    public:
       // bool canChangeColour;
       // bool isOriginalColour;
        bool movingRight;
    private:
        vector<Enemy> enemies;
        unsigned int gameRow;
        float spacing;
        unsigned int numEnemies;
};

#endif // ENEMYROW_H
