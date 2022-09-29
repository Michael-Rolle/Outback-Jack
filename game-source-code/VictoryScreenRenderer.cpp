#include "VictoryScreenRenderer.h"

VictoryScreenRenderer::VictoryScreenRenderer(sf::Font* font)
{
    winText.setFont(*font);
    restartText.setFont(*font);
    winText.setString("You Win!");
    restartText.setString("Press Space to Replay");
    winText.setOrigin(winText.getLocalBounds().width/2.0f, winText.getLocalBounds().height/2.0f);
    restartText.setOrigin(restartText.getLocalBounds().width/2.0f, restartText.getLocalBounds().height/2.0f);
    winText.setPosition(1920/2.0f, 0.3*1080);
    restartText.setPosition(1920/2.0f, 0.6*1080);
    winText.setScale(0.33.0f*1920.0f/winText.getLocalBounds().width, 0.33.0f*1920.0f/winText.getLocalBounds().height)
}

void VictoryScreenRenderer::draw(sf::RenderWindow& window)
{
    window.draw(winText);
    window.draw(restartText);
}
