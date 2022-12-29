#include "Score.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <vector>
#include "GameMode.h"

Score::Score(const float gameWidth, const float gameHeight, GameMode gameMode):
    highScoreFileReader{"resources/highscore.txt"}
{
    if(!font.loadFromFile("resources/I-Have-Bad-News.ttf"))
        throw "cannot load font file";

    points = vector<sf::Text>(2);
    labels = vector<sf::Text>(2);
    scores = vector<int>(2);

    if(gameMode == GameMode::Singleplayer)
    {
        points.pop_back();
        labels.pop_back();
        scores.pop_back();
    }

    auto count = 0;
    for(auto& point: points)
    {
        point.setFont(font);
        point.setCharacterSize(50);
        if(count == 0)
            point.setFillColor(sf::Color::Green);
        else
            point.setFillColor(sf::Color::Red);
        point.setString("0");
        point.setLetterSpacing(3);
        point.setOutlineThickness(3);
        point.setOutlineColor(sf::Color::White);

        sf::FloatRect pointsRect = point.getLocalBounds();

        point.setOrigin(pointsRect.left + pointsRect.width/2.0f, pointsRect.top + pointsRect.height/2.0f);
        if(count == 0)
            point.setPosition(gameWidth/4.75, gameHeight/2 - 10*point.getCharacterSize());
        else
            point.setPosition(1775, gameHeight/2 - 10*point.getCharacterSize());//1712.43
        count += 1;
    }

    count = 0;
    for(auto& label: labels)
    {
        label.setFont(font);
        label.setCharacterSize(50);
        if(count == 0)
            label.setFillColor(sf::Color::Green);
        else
            label.setFillColor(sf::Color::Red);
        label.setString("Score - ");
        label.setLetterSpacing(3);
        label.setOutlineThickness(2);
        label.setOutlineColor(sf::Color::White);

        sf::FloatRect labelRect = label.getLocalBounds();

        label.setOrigin(labelRect.left + labelRect.width/2.0f, labelRect.top + labelRect.height/2.0f);
        if(count == 0)
            label.setPosition(gameWidth/9.25 , gameHeight/2 - 10*label.getCharacterSize());
        else
            label.setPosition(1580, gameHeight/2 - 10*label.getCharacterSize());//1515.79
        count += 1;
    }

    highScore = stoi(highScoreFileReader.read());
    highScoreText.setFont(font);
    highScoreText.setCharacterSize(50);
    highScoreText.setFillColor(sf::Color::White);
    highScoreText.setString("Highscore - " + highScoreFileReader.read());
    highScoreText.setLetterSpacing(3);
    highScoreText.setOutlineThickness(2);
    highScoreText.setOutlineColor(sf::Color::Yellow);
    sf::FloatRect highScoreRect = highScoreText.getLocalBounds();
    highScoreText.setOrigin(highScoreRect.left + highScoreRect.width/2.0f, highScoreRect.top + highScoreRect.height/2.0f);
    highScoreText.setPosition(gameWidth/2.0f, gameHeight/2.0f - 10*highScoreText.getCharacterSize());

    for(auto& score: scores)
    {
        score = 0;
    }
}

void Score::draw(sf::RenderWindow& window)
{
    for(auto& point: points)
        window.draw(point);
    for(auto& label: labels)
        window.draw(label);
    window.draw(highScoreText);
}

void Score::update(Jack& player)
{
    player.score += 10;
    scores.at(player.playerNum-1) = player.score;
    points.at(player.playerNum-1).setString(std::to_string(scores.at(player.playerNum-1)));
}

void Score::reset()
{
    for(auto& score: scores)
        score = 0;
    for(auto& point: points)
        point.setString("0");
    highScore = stoi(highScoreFileReader.read());
    highScoreText.setString("Highscore - " + highScoreFileReader.read());
}

void Score::updateFromTemp(Jack& player, Temperature& temperature)
{
    if(temperature.temp >= 50.0f)
        return;
    temperature.temp++;
    temperature.temperature.setString(std::to_string((int)floor(temperature.temp)));
    player.score += 2.0f;
    scores.at(player.playerNum-1) = player.score;
    points.at(player.playerNum-1).setString(std::to_string(scores.at(player.playerNum-1)));

    if(scores.at(player.playerNum-1) > highScore)
    {
        highScoreFileReader.write(to_string(scores.at(player.playerNum-1)));
    }
}
