#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H
#include "EnemyRow.h"
#include <vector>

using namespace std;

class EnemyController
{
    public:
        EnemyController(sf::Texture* texture, float pos);
        EnemyController(){};
        void update(float deltaTime);
        void draw(sf::RenderWindow& window);
        EnemyRow* getEnemyRow(const unsigned int row); //enter a row num from 1 to 4
        vector<float> getEnemyPositions(const unsigned int row); //enter a row num from 1 to 4

    private:
        vector<EnemyRow> enemyRows;
};

#endif // PLATFORMCONTROLLER_H
