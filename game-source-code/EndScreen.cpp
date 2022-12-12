#include "EndScreen.h"
#include <SFML/Graphics.hpp>
#include "PlayerNumber.h"

EndScreen::EndScreen(const float gameWidth, const float gameHeight)
{
    if(!font.loadFromFile("resources/I-Have-Bad-News.ttf"))
        throw "cannot load font";
    text.setFont(font);
    text.setCharacterSize(75);
    text.setLetterSpacing(3);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Red);
    text.setOutlineThickness(3);
    text.setOrigin(text.getLocalBounds().width/2.0f, text.getLocalBounds().height/2.0f);
    text.setPosition(gameWidth/2.0f, 0.3*gameHeight);
}

 void EndScreen::displayWin(PlayerNumber num)
 {
    switch(num)
    {
        case PlayerNumber::One:
            text.setString("PLAYER ONE WINS!\n\nPRESS SPACE TO REPLAY");
            break;
        case PlayerNumber::Two:
            text.setString("PLAYER TWO WINS!\n\nPRESS SPACE TO REPLAY");
            break;
        default:
            throw "invalid player number";
    }
 }

 void EndScreen::draw(sf::RenderWindow& window)
 {
     window.draw(text);
 }
