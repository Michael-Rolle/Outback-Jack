#ifndef PLATFORMCONTROLLER_H
#define PLATFORMCONTROLLER_H
#include "PlatformRow.h"
#include <vector>

/*!
Class capable of creating, updating and reading each platform row (and hence each platform as well) that exists.
*/

using namespace std;

class PlatformController
{
    public:
        PlatformController(sf::Texture* texture);
        PlatformController(){};
        void changePlatformRowColour(unsigned int row, sf::Texture* texture, bool original); /*!<  */
        void update(float deltaTime); /*!<  */
        void draw(sf::RenderWindow& window); /*!<  */
        bool allPlatformsNewColour(); /*!<  */
        PlatformRow* getPlatformRow(const unsigned int row); /*!<  */
        vector<float> getPlatformPositions(const unsigned int row); /*!<  */

    private:
        vector<PlatformRow> platformRows;
};

#endif // PLATFORMCONTROLLER_H
