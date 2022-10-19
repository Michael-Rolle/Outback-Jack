#ifndef PLATFORMCONTROLLER_H
#define PLATFORMCONTROLLER_H
#include "PlatformRow.h"
#include <vector>

/*!
Class capable of creating, updating and reading each platform row (and hence each platform as well) that exists. Member functions
only accept rows 1 to 4 when they have an 'unsigned int row' or 'const unsigned int row' parameter.
*/

using namespace std;

class PlatformController
{
    public:
        PlatformController(sf::Texture* texture);
        PlatformController(){};
        void changePlatformRowColour(unsigned int row, sf::Texture* texture, bool original); /*!< Changes the platform row colour
        to that of the Texture parameter for a specified row given as the input integer. The bool is used to track if the row is
        its original colour or not. */
        void update(float deltaTime); /*!< Updates each platform within a row for all rows using the parameter float. */
        void draw(sf::RenderWindow& window); /*!< Draws each platform within a row for all rows with reference to a RenderWindow. */
        bool allPlatformsNewColour(); /*!< Returns a bool indicating if all existing platforms are no longer their original colour. */
        PlatformRow* getPlatformRow(const unsigned int row); /*!< Returns the PlatformRow respective to the parameter. */
        vector<float> getPlatformPositions(const unsigned int row); /*!< Returns a vector of floats containing all the horizontal
        positions of the platforms within a row specified by the paramter. */

    private:
        vector<PlatformRow> platformRows;
};

#endif // PLATFORMCONTROLLER_H
