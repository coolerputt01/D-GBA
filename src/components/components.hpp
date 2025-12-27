#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "../config/config.hpp"

struct Label{
    std::string text;
    sf::Text textDisplay;
    sf::Font font;

    Label(const std::string& txt) : font(FONT_FILE),textDisplay(font){
        text = txt;
        textDisplay.setString(text);
    }

    void draw(sf::RenderWindow& window){
        textDisplay.setString(text);
        window.draw(textDisplay);
    }
};