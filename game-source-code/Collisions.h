#ifndef COLLISIONS_H
#define COLLISIONS_H
#include "PlatformController.h"
#include "Jack.h"

class Collisions
{
    public:
        Collisions(Jack& player, PlatformController& platforms);
        void update();

    private:
        Jack player;
        PlatformController platforms;
};

#endif // COLLISIONS_H
