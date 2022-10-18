#ifndef ENEMYCONTROLLER_H
#define ENEMYCONTROLLER_H
#include "EnemyRow.h"
#include <vector>

/*!
Class capable of updating and reading each enemy row (and hence each enemy as well) that exists.
*/

using namespace std;

class EnemyController
{
    public:
        EnemyController(sf::Texture* texture, float pos);
        EnemyController(){};
        void update(float deltaTime); /*!< Takes in a float to update each enemy row postition that exists. */
        void draw(sf::RenderWindow& window); /*!< Draws each enemy row with reference to a RenderWindow. */
        EnemyRow* getEnemyRow(const unsigned int row); /*!< Returns the EnemyRow respective to the parameter.
                                                            Enemies can only exist in rows 1 to 4.*/
        vector<float> getEnemyPositions(const unsigned int row); /*!< Returns a vector of type float, containing the
            the positions of all enemies within a row respective to the parameter. Enemies can only exist in rows 1 to 4. */

    private:
        vector<EnemyRow> enemyRows;
};

#endif // PLATFORMCONTROLLER_H
