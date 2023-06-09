#include "Tent.h"

Tent::Tent(sf::Texture* texture, unsigned int rows, unsigned int columns, float height, float horizontalPosition)
{
    this->height = height;
    tent.setTexture(*texture);
    tent.scale(height*rows/tent.getLocalBounds().width, height*rows/tent.getLocalBounds().height);
    tent.setPosition(horizontalPosition, 310); //assuming the origin of the tent will be the bottom of the tent
    numFrames.x = columns;
    numFrames.y = rows;
    currentFrame.x = 0;
    currentFrame.y = 1;
    textRect.height = tent.getLocalBounds().height/(float)numFrames.y;
    textRect.width = tent.getLocalBounds().width/(float)numFrames.x;
    textRect.left = tent.getLocalBounds().width;
    textRect.top = tent.getLocalBounds().height;
    tent.setTextureRect(textRect);
    built = false;
}

void Tent::nextFrame()
{
    if(built)
        return;
    if(currentFrame.x == numFrames.x && currentFrame.y != numFrames.y)
    {
        currentFrame.x = 1;
        currentFrame.y += 1;
    }
    else if(currentFrame.x < numFrames.x)
    {
        currentFrame.x += 1;
    }

    if(currentFrame.x == numFrames.x && currentFrame.y == numFrames.y)
        built = true;

    textRect.left = (currentFrame.x-1)*textRect.width;
    textRect.top = (currentFrame.y-1)*textRect.height;

    tent.setTextureRect(textRect);
    tent.setOrigin(textRect.width/2.0f, textRect.height);
}

void Tent::removeFrame()
{
    if(currentFrame.x == 0)
        return;

    if(currentFrame.x == 1 && currentFrame.y == 1)
    {
        currentFrame.x = 0;
        textRect.left = tent.getLocalBounds().width;
        textRect.top = tent.getLocalBounds().height;
        tent.setTextureRect(textRect);
    }
    else if(currentFrame.x == 1 && currentFrame.y != 1)
    {
        currentFrame.x = numFrames.x;
        currentFrame.y -= 1;
    }
    else if(currentFrame.x == numFrames.x && currentFrame.y == numFrames.y)
    {
        currentFrame.x -= 1;
        built = false;
    }
    else
    {
        currentFrame.x -= 1;
    }

    textRect.left = (currentFrame.x-1)*textRect.width;
    textRect.top = (currentFrame.y-1)*textRect.height;

    tent.setTextureRect(textRect);
    tent.setOrigin(textRect.width/2.0f, textRect.height);
}

float Tent::getPositionX()
{
    return tent.getPosition().x;
}

float Tent::width()
{
    return tent.getGlobalBounds().width;
}

void Tent::draw(sf::RenderWindow& window)
{
    window.draw(tent);
}

void Tent::reset()
{
    currentFrame.x = 0;
    currentFrame.y = 1;
    textRect.height = tent.getLocalBounds().height;
    textRect.width = tent.getLocalBounds().width;
    textRect.left = tent.getLocalBounds().width*numFrames.x;
    textRect.top = tent.getLocalBounds().height*numFrames.y;
    tent.setTextureRect(textRect);
    built = false;
}
