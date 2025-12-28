#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdint>
#include <cassert>
#include "./components/components.hpp"
#include "./components/bus.hpp"


using std::cout;


int main(){
    sf::RenderWindow window(sf::VideoMode({720,480}),"D-gba");
    window.setFramerateLimit(60);

    //FPS counter
    Label text = Label("FPS: ");
    Bus bus;
    sf::Clock clock;
    float fps = 0.0f;
    auto rom_loaded = bus.rom.load();
    if (rom_loaded == 0 || rom_loaded == 3 ){
        return 1;
    }
    bus.write8(0x02000000,0x12);
    uint8_t test = bus.read8(0x02000000);

    std::cout<<"Test value: "<<test<<"\n";


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