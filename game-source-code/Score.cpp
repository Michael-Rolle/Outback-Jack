#include "Score.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>

Score::Score(const float gameWidth, const float gameHeight)
{
    if(!font.loadFromFile("resources/I-Have-Bad-News.ttf"))
        throw "cannot load font file";

    points.setFont(font);
    points.setCharacterSize(50);
    points.setFillColor(sf::Color::Blue);
    points.setString("0");
    points.setLetterSpacing(3);
    points.setOutlineThickness(3);
    points.setOutlineColor(sf::Color::White);

    sf::FloatRect pointsRect = points.getLocalBounds();

    points.setOrigin(pointsRect.left + pointsRect.width/2.0f, pointsRect.top + pointsRect.height/2.0f);
    points.setPosition(gameWidth/4.75, gameHeight/2 - 8.15*points.getCharacterSize());

    label.setFont(font);
    label.setCharacterSize(50);
    label.setFillColor(sf::Color::Blue);
    label.setString("Score - ");
    label.setLetterSpacing(3);
    label.setOutlineThickness(3);
    label.setOutlineColor(sf::Color::White);

    sf::FloatRect labelRect = label.getLocalBounds();

    label.setOrigin(labelRect.left + labelRect.width/2.0f, labelRect.top + labelRect.height/2.0f);
    label.setPosition(gameWidth/9.25 , gameHeight/2 - 8*label.getCharacterSize());

    score = 0;
}

void Score::draw(sf::RenderWindow& window)
{
    window.draw(points);
    window.draw(label);
}

void Score::update(Jack& player)
{
    player.score += 10;
    score = player.score;
    points.setString(std::to_string(score));
}

void Score::reset()
{
    score = 0;
    points.setString(std::to_string(score));
}

void Score::updateFromTemp(Jack& player, Temperature& temperature)
{
    if(temperature.temp >= 50.0f)
        return;
    temperature.temp++;
    temperature.temperature.setString(std::to_string((int)floor(temperature.temp)));
    player.score += 2.0f;
    score = player.score;
    points.setString(std::to_string(score));
}
