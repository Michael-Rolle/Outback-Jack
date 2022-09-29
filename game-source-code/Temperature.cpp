#include "Temperature.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>

Temperature::Temperature(const float gameWidth, const float gameHeight)
{
    if(!font.loadFromFile("resources/I-Have-Bad-News.ttf"))
        throw "cannot load font file";

    temperature.setFont(font);
    temperature.setCharacterSize(50);
    temperature.setFillColor(sf::Color::White);
    temperature.setString("");
    temperature.setLetterSpacing(3);
    temperature.setOutlineThickness(3);
    temperature.setOutlineColor(sf::Color::Red);

    sf::FloatRect temperatureRect = temperature.getLocalBounds();

    temperature.setOrigin(temperatureRect.left + temperatureRect.width/2.0f, temperatureRect.top + temperatureRect.height/2.0f);
    temperature.setPosition(gameWidth/50, gameHeight/2 - 10*temperature.getCharacterSize());

    degrees.setFont(font);
    degrees.setCharacterSize(10);
    degrees.setFillColor(sf::Color::White);
    degrees.setString("o");
    degrees.setLetterSpacing(3);
    degrees.setOutlineThickness(3);
    degrees.setOutlineColor(sf::Color::Red);

    sf::FloatRect degreesRect = degrees.getLocalBounds();

    degrees.setOrigin(degreesRect.left + degreesRect.width/2.0f, degreesRect.top + degreesRect.height/2.0f);
    degrees.setPosition(gameWidth/13, gameHeight/2 - 50*degrees.getCharacterSize());
}

void Temperature::draw(sf::RenderWindow& window)
{
    window.draw(temperature);
    window.draw(degrees);
}

void Temperature::update(sf::RenderWindow& window, float deltaTime)
{
    totalTime += deltaTime;
    int time = round(totalTime);
    temperature.setString(std::to_string(time));
}
