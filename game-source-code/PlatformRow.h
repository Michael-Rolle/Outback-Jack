#ifndef PLATFORMROW_H
#define PLATFORMROW_H
#include "Platform.h"
#include <vector>

/*!
Creates a row of platforms capable of being moved and updated as one unit.
*/

using namespace std;

class PlatformRow
{
    public:
        PlatformRow(sf::Texture* texture, const unsigned int numPlatforms, const float spacing, const unsigned int gameRow, const bool movingRight);
        ~PlatformRow(){}
        vector<float> platformPositions();
        /*!< Returns a vector of floats containing all the horizontal positions of the platforms within the PlatformRow. */
        Platform getPlatform(const unsigned int platformNum){ return platforms.at(platformNum-1); }
        /*!< Returns the Platform object within the row, specified by the input integer. Input integer must be less than or equal to 'const unsigned int numPlatforms' but larger than one. */
        void changeDirection();
        /*!< Reverses the direction of each platform within the PlatfromRow. Direction only changes between left and right. */
        void changeColour(sf::Texture* texture, bool original);
        /*!< Changes each platforms colour, within the PlatformRow, to that specified by the Texture Parameter. The bool tracks if each platform is its original colour or not. */
        void update(float deltaTime);
        /*!< Updates each platforms', within the PlatformRow, horizontal position using the float parameter. */
        void draw(sf::RenderWindow& window);
        /*!< Draws each platform within the PlatformRow with reference to a RenderWindow. */

    public:
        bool canChangeColour;
        bool isOriginalColour;
        bool movingRight;
    private:
        vector<Platform> platforms;
        unsigned int gameRow;
        float spacing;
        unsigned int numPlatforms;
};

#endif // PLATFORMROW_H
