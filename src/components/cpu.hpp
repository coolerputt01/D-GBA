#pragma once
#include <cstdint>
#include "bus.hpp"

class CPU {
    public:
        Bus* bus;
        uint16_t flags;
        uint32_t registers[16];
    
    void step(){
        uint32_t program_counter = registers[15];
        uint32_t instruction = bus->read32(program_counter);

        if (instruction == 0xE1A00000){
            return;
        }else if((instruction & 0x0FE00000) == 0x02800000){
            uint32_t register_destination = (instruction >> 12) & 0xF;
            uint32_t register_source = (instruction >> 16) & 0xF;

            uint32_t intermidiate_op = instruction & 0xFFF;

            registers[register_destination] = registers[register_source] + intermidiate_op;
        }

        registers[15] += 4;
    }

};