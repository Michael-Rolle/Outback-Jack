#ifndef FISHCONTROLLER_H
#define FISHCONTROLLER_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Enemy.h"

/*!
Behaves similarily to EnemyController. Class capable of creating, updating and reading a fish row (and hence each individual fish as well) that exists.
*/

using std::vector;

class FishController
{
    public:
        FishController(sf::Texture* fishTexture, const unsigned int numFish, const float spacing);
        FishController(){}
        vector<float> fishPositions();
        /*!< Returns a vector of type float containing the positions of all fish within the row. Only one row so no need for a parameter.*/
        unsigned int row(){ return gameRow; }
        /*!< Returns the integer value of the current row the fish exist in. */
        Enemy getFish(unsigned int fishNum){ return *fishRow.at(fishNum-1); }
        /*!< Returns the fish (of type Enemy) specified by the parameter. The input integer must be less than or equal to the number of created fish. */
        void removeFish(unsigned int fishNum);
        /*!< Removes the specified fish from the row of existing fish. The input integer must be less than or equal to the number of created fish. */
        void update(float deltaTime);
        /*!< Update the positions of all fish within a row respective to the parameter. If no row of fish exists, create a new row of fish. */
        void draw(sf::RenderWindow& window);
        /*!< Draw all fish within a row of fish with reference to a RenderWindow. */
    private:
        void newFishRow();

    private:
        vector<Enemy*> fishRow;
        unsigned int gameRow;
        unsigned int numFish;
        float spacing;
        bool movingRight;
        sf::Texture fishText;
};

#endif // FISHCONTROLLER_H
