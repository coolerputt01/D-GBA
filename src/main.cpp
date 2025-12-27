#include <SFML/Graphics.hpp>
#include <iostream>
#include "./components/components.hpp"
#include "./components/roms.hpp"


using std::cout;


int main(){
    sf::RenderWindow window(sf::VideoMode({720,480}),"D-gba");
    window.setFramerateLimit(60);

    //FPS counter
    Label text = Label("FPS: ");
    Rom rom;
    sf::Clock clock;
    float fps = 0.0f;
    bool rom_loaded = rom.load();
    if (!rom_loaded){
        return 1;
    }


    while (window.isOpen()){

        float delta = clock.restart().asSeconds();
        fps = 1.0f/ delta;
        while(const std::optional<sf::Event> event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
            window.close();
        }
        window.clear();
        text.text = std::string("FPS: ") + std::to_string(static_cast<int>(fps));
        text.draw(window);
        window.display();
    }
    
    return 0;
}