#include "Animation.h"
#include <cmath>

Animation::Animation(sf::Texture* texture, sf::Vector2u frameCount, float switchTime)
{
    this->frameCount = frameCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentFrame.x = 0;

    textRect.width = texture->getSize().x / float(frameCount.x);
    textRect.height = texture->getSize().y / float(frameCount.y);
}

void Animation::update(int row, float deltaTime, bool facingRight)
{
    currentFrame.y = row;
    totalTime += deltaTime;

    if(totalTime >= switchTime)
    {
        totalTime -= switchTime;
        currentFrame.x++;

        if(currentFrame.x >= frameCount.x)
        {
            currentFrame.x = 0;
        }
    }


    textRect.top = currentFrame.y * textRect.height;

    if(facingRight)
    {
        textRect.left = currentFrame.x * textRect.width;
        textRect.width = abs(textRect.width);
    }
    else //flips row of animation to face the other direction
    {
        textRect.left = (currentFrame.x + 1) * abs(textRect.width);
        textRect.width = -abs(textRect.width);
    }

}
