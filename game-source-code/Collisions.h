#ifndef COLLISIONS_H
#define COLLISIONS_H
#include "PlatformController.h"
#include "Jack.h"

class Collisions
{
    public:
        Collisions(float platformWidth, float platformSpeed);
        void update(Jack& player, PlatformController& platforms);

    private:
        float platformWidth;
        float platformSpeed;
};

#endif // COLLISIONS_H
