#include "EnemyController.h"
#include "EnemyRow.h"
#include <vector>

using namespace std;

EnemyController::EnemyController(sf::Texture* texture, float pos)
{
    bool direction = true;
    for(int i = 0; i < 4; i++)
    {
        auto enemyRow = EnemyRow{texture, 3, 10, (unsigned int)(i+2), direction, pos};
        direction = !direction;
        enemyRows.push_back(enemyRow);
    }
}

void EnemyController::update(float deltaTime)
{
    for(auto& enemyRow : enemyRows)
        enemyRow.update(deltaTime);
}

void EnemyController::draw(sf::RenderWindow& window)
{
    for(auto& enemyRow : enemyRows)
        enemyRow.draw(window);
}

EnemyRow* EnemyController::getEnemyRow(const unsigned int row)
{
    return &enemyRows.at(row-1);
}

vector<float> EnemyController::getEnemyPositions(const unsigned int row)
{
    auto positions = enemyRows.at(row-1).enemyPositions();
    return positions;
}
