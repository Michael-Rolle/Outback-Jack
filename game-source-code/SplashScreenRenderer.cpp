#include "SplashScreenRenderer.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

SplashScreenRenderer::SplashScreenRenderer(const float gameWidth, const float gameHeight)
{
    //Font
    if(!font.loadFromFile("resources/I-Have-Bad-News.ttf"))
        throw "cannot load font file";

    //Text
    title.setFont(font);
    startMessage.setFont(font);
    title.setCharacterSize(100);
    startMessage.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    startMessage.setFillColor(sf::Color::Red);
    title.setString("OUTBACK  JACK");
    startMessage.setString("Press  Space  to  Play");
    title.setLetterSpacing(3);
    startMessage.setLetterSpacing(3);
    title.setOutlineThickness(3);
    title.setOutlineColor(sf::Color::Red);
    startMessage.setOutlineThickness(2);
    startMessage.setOutlineColor(sf::Color::White);

    // Centre text
    sf::FloatRect titleRect = title.getLocalBounds();
    sf::FloatRect startRect = startMessage.getLocalBounds();
    title.setOrigin(titleRect.left + titleRect.width/2.0f, titleRect.top + titleRect.height/2.0f);
    title.setPosition(gameWidth/2, gameHeight/2 - 3.5*title.getCharacterSize());
    startMessage.setOrigin(startRect.left + startRect.width/2.0f, startRect.top + startRect.height/2.0f);
    startMessage.setPosition(title.getPosition().x, title.getPosition().y + 2*title.getCharacterSize());

    //Background image
    if(!background.loadFromFile("resources/start_background.jpg"))
        throw "cannot load background image";
    backgroundImage.setTexture(background);
    backgroundImage.setScale(gameWidth/backgroundImage.getLocalBounds().width, gameHeight/backgroundImage.getLocalBounds().height);
    sf::FloatRect picRect = backgroundImage.getLocalBounds();
    backgroundImage.setOrigin(picRect.left + picRect.width/2.0f, picRect.top + picRect.height/2.0f);
    backgroundImage.setPosition(gameWidth/2.0f, gameHeight/2.0f);

    //Controls image
    if(!controls_1.loadFromFile("resources/wasd.png"))
        throw "cannot load player ones controls image";
    controls_1_Image.setTexture(controls_1);
    controls_1_Image.setScale(gameWidth/(6.0f*controls_1_Image.getLocalBounds().width), gameHeight/(5.0f*controls_1_Image.getLocalBounds().height));
    sf::FloatRect wasdRect = controls_1_Image.getLocalBounds();
    controls_1_Image.setOrigin(wasdRect.left + wasdRect.width/2.0f, wasdRect.top + wasdRect.height/2.0f);
    controls_1_Image.setPosition(gameWidth/9.0f, gameHeight/1.25f);

    if(!controls_1_Shift.loadFromFile("resources/Shift.png"))
        throw "cannot load player ones shift controls image";
    controls_1_Shift_Image.setTexture(controls_1_Shift);
    controls_1_Shift_Image.setScale(gameWidth/(14.0f*controls_1_Shift_Image.getLocalBounds().width), gameHeight/(10.0f*controls_1_Shift_Image.getLocalBounds().height));
    sf::FloatRect shift_1_Rect = controls_1_Shift_Image.getLocalBounds();
    controls_1_Shift_Image.setOrigin(shift_1_Rect.left + shift_1_Rect.width/2.0f, shift_1_Rect.top + shift_1_Rect.height/2.0f);
    controls_1_Shift_Image.setPosition(gameWidth/27.0f, gameHeight/1.05f);

    if(!controls_2.loadFromFile("resources/arrows.png"))
        throw "cannot load player two controls image";
    controls_2_Image.setTexture(controls_2);
    controls_2_Image.setScale(gameWidth/(6.0f*controls_2_Image.getLocalBounds().width), gameHeight/(5.0f*controls_2_Image.getLocalBounds().height));
    sf::FloatRect arrowsRect = controls_2_Image.getLocalBounds();
    controls_2_Image.setOrigin(arrowsRect.left + arrowsRect.width/2.0f, arrowsRect.top + arrowsRect.height/2.0f);
    controls_2_Image.setPosition(gameWidth/1.13f, gameHeight/1.25f);

    //Controls text
    player_1.setFont(font);
    player_1.setCharacterSize(20);
    player_1.setFillColor(sf::Color::White);
    player_1.setString("PLAYER  1  CONTROLS");
    player_1.setLetterSpacing(3);
    player_1.setOutlineThickness(3);
    player_1.setOutlineColor(sf::Color::Red);
    sf::FloatRect player_1_Rect = player_1.getLocalBounds();
    player_1.setOrigin(player_1_Rect.left + player_1_Rect.width/2.0f, player_1_Rect.top + player_1_Rect.height/2.0f);
    player_1.setPosition(gameWidth/9, gameHeight/1.6);

    player_2.setFont(font);
    player_2.setCharacterSize(20);
    player_2.setFillColor(sf::Color::White);
    player_2.setString("PLAYER  2  CONTROLS");
    player_2.setLetterSpacing(3);
    player_2.setOutlineThickness(3);
    player_2.setOutlineColor(sf::Color::Red);
    sf::FloatRect player_2_Rect = player_2.getLocalBounds();
    player_2.setOrigin(player_2_Rect.left + player_2_Rect.width/2.0f, player_2_Rect.top + player_2_Rect.height/2.0f);
    player_2.setPosition(gameWidth/1.13f, gameHeight/1.6);

    controls_1_text.setFont(font);
    controls_1_text.setCharacterSize(15);
    controls_1_text.setFillColor(sf::Color::Black);
    controls_1_text.setString(" \t\t\t\t\t\t\t\t\t\t\t\t  JUMP  UP  \n\n\n\n\n\n\n     MOVE  LEFT \t\t\t\t\t\t\t\t\t\t MOVE  RIGHT  \n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t  JUMP  DOWN");
    controls_1_text.setLetterSpacing(3);
    controls_1_text.setOutlineThickness(3);
    controls_1_text.setOutlineColor(sf::Color::White);
    sf::FloatRect controls_1_text_Rect = controls_1_text.getLocalBounds();
    controls_1_text.setOrigin(controls_1_text_Rect.left + controls_1_text_Rect.width/2.0f, controls_1_text_Rect.top + controls_1_text_Rect.height/2.0f);
    controls_1_text.setPosition(gameWidth/9, gameHeight/1.25);



    controls_2_text.setFont(font);
    controls_2_text.setCharacterSize(15);
    controls_2_text.setFillColor(sf::Color::Black);
    controls_2_text.setString(" \t\t\t\t\t\t\t\t\t\t\t\t  JUMP  UP  \n\n\n\n\n\n\n     MOVE  LEFT \t\t\t\t\t\t\t\t\t\t MOVE  RIGHT  \n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t  JUMP  DOWN");
    controls_2_text.setLetterSpacing(3);
    controls_2_text.setOutlineThickness(3);
    controls_2_text.setOutlineColor(sf::Color::White);
    sf::FloatRect controls_2_text_Rect = controls_2_text.getLocalBounds();
    controls_2_text.setOrigin(controls_2_text_Rect.left + controls_2_text_Rect.width/2.0f, controls_2_text_Rect.top + controls_2_text_Rect.height/2.0f);
    controls_2_text.setPosition(gameWidth/1.13f, gameHeight/1.25);
}

void SplashScreenRenderer::draw(sf::RenderWindow& window)
{
    window.draw(backgroundImage);
    window.draw(title);
    window.draw(startMessage);
    window.draw(controls_1_text);
    window.draw(controls_2_text);
    window.draw(player_1);
    window.draw(player_2);
    window.draw(controls_1_Image);
    window.draw(controls_1_Shift_Image);
    window.draw(controls_2_Image);
}
