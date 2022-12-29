#include "EndScreen.h"
#include <SFML/Graphics.hpp>
#include "PlayerNumber.h"

EndScreen::EndScreen(const float gameWidth, const float gameHeight)
{
    if(!font.loadFromFile("resources/I-Have-Bad-News.ttf"))
        throw "cannot load font";
    text.setFont(font);
    replayText.setFont(font);
    text.setString("PLAYER  ONE  WINS!");
    replayText.setString("PRESS  BACKSPACE  TO  REPLAY");
    text.setCharacterSize(100);
    replayText.setCharacterSize(50);
    text.setLetterSpacing(3);
    replayText.setLetterSpacing(3);
    text.setFillColor(sf::Color::White);
    replayText.setFillColor(sf::Color::Red);
    text.setOutlineColor(sf::Color::Red);
    replayText.setOutlineColor(sf::Color::White);
    text.setOutlineThickness(3);
    replayText.setOutlineThickness(3);
    text.setOrigin(text.getLocalBounds().width/2.0f, text.getLocalBounds().height/2.0f);
    replayText.setOrigin(replayText.getLocalBounds().width/2.0f, replayText.getLocalBounds().height/2.0f);
    text.setPosition(gameWidth/2.0f, 0.3*gameHeight);
    replayText.setPosition(gameWidth/2.0f, 0.6*gameHeight);
}

 void EndScreen::displayWin(PlayerNumber num)
 {
    switch(num)
    {
        case PlayerNumber::One:
            text.setString("PLAYER  ONE  WINS!");
            text.setOrigin(text.getLocalBounds().width/2.0f, text.getLocalBounds().height/2.0f);
            text.setPosition(1920.0f/2.0f, 0.3*1080.0f);
            break;
        case PlayerNumber::Two:
            text.setString("PLAYER  TWO  WINS!");
            text.setOrigin(text.getLocalBounds().width/2.0f, text.getLocalBounds().height/2.0f);
            text.setPosition(1920.0f/2.0f, 0.3*1080.0f);
            break;
        case PlayerNumber::Neither:
            text.setString("DEFEAT!");
            text.setOrigin(text.getLocalBounds().width/2.0f, text.getLocalBounds().height/2.0f);
            text.setPosition(1920.0f/2.0f, 0.3*1080.0f);
            break;
        default:
            throw "invalid player number";
    }
 }

 void EndScreen::draw(sf::RenderWindow& window)
 {
     window.draw(text);
     window.draw(replayText);
 }
