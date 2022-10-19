#ifndef PLATFORMROW_H
#define PLATFORMROW_H
#include "Platform.h"
#include <vector>

/*!

*/

using namespace std;

class PlatformRow
{
    public:
        PlatformRow(sf::Texture* texture, const unsigned int numPlatforms, const float spacing, const unsigned int gameRow, const bool movingRight);
        ~PlatformRow(){}
        vector<float> platformPositions(); /*!<  */
        Platform getPlatform(const unsigned int platformNum){ return platforms.at(platformNum-1); } /*!<  */
        void changeDirection(); /*!<  */
        void changeColour(sf::Texture* texture, bool original); /*!<  */
        void update(float deltaTime); /*!<  */
        void draw(sf::RenderWindow& window); /*!<  */

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
