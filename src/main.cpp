#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdint>
#include <cassert>
#include "./components/components.hpp"
#include "./components/cpu.hpp"


using std::cout;


int main(){
    sf::RenderWindow window(sf::VideoMode({720,480}),"D-gba");
    window.setFramerateLimit(60);

    //FPS counter
    Label text = Label("FPS: ");
    CPU cpu;
    Bus bus;
    cpu.registers[0] = 10;
    cpu.registers[4] = 22;
    cpu.registers[15] = 0x02000000;
    cpu.flags = 0;
    sf::Clock clock;
    float fps = 0.0f;
    auto rom_loaded = bus.rom.load();
    cpu.bus = &bus;
    if(rom_loaded == 0 || rom_loaded == 3 ){
        return 1;
    }
    bus.write32(0x02000000, 0xE2800007);
    cpu.step();
    cpu.printFlags();
    std::cout << "R0 = " << cpu.registers[0] << "\n";
    std::cout << "PC = " << std::hex << cpu.registers[15] << "\n";


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