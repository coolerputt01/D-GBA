#pragma once
#include <cstdint>
#include "bus.hpp"

enum FLAG {
    FLAG_N = 1U << 31,
    FLAG_Z = 1U << 30,
    FLAG_C = 1U << 29,
    FLAG_V = 1U << 28
};

bool conditionPassed(uint32_t instruction, uint32_t cspr_flags){
    uint32_t condition = (instruction >> 28) & 0xF;
    bool N = cspr_flags & FLAG_N;
    bool Z = cspr_flags & FLAG_Z;
    bool C = cspr_flags & FLAG_C;
    bool V = cspr_flags & FLAG_V;

    switch (condition)
    {
    case 0x0: 
        return Z;
    case 0x1: 
        return !Z;
    case 0x2: 
        return C;
    case 0x3:
        return !C;
    case 0x4:
        return N;
    case 0x5:
        return !N;
    case 0x6:
        return V;
    case 0x7:
        return !V;
    case 0x8: 
        return C && !Z; 
    case 0x9:
        return !C && !Z;
    case 0xA: 
        return N == V; 
    case 0xB:
        return N != V;  
    case 0xC:
        return !Z && (N == V); 
    case 0xD:
        return Z || (N != V);
    case 0xE:
        return true; 
    
    default:
        return false;
    }

}


class CPU {
    public:
        Bus* bus;
        uint32_t flags;
        uint32_t registers[16];
    
    void step(){
        uint32_t program_counter = registers[15];
        uint32_t instruction = bus->read32(program_counter);

        registers[15] += 4;

        if (instruction == 0xE1A00000)
            return;

        if (!conditionPassed(instruction, flags))
            return;

        uint32_t instructionClass = (instruction >> 25 ) & 0x7;

        switch(instructionClass){
            case 0b001:
            case 0b000:
                break;
            case 0b010:
            case 0b011:
                break;
            default:
                break;
        }
    }


    void execute(uint32_t instruction){
        bool intermmediate = (instruction >> 25) & 1;
        uint32_t opcode = (instruction >> 21) & 0xF;
        bool instruction_flags =(instruction >> 20) & 1;
    
        uint32_t flexible_constant;
    
        if(intermmediate){
            uint32_t bit8_intermmediate_rot = (instruction & 0xFF);
            uint32_t rotating_amount = ((instruction >> 8) & 0xF) * 2;
            flexible_constant = (bit8_intermmediate_rot >> rotating_amount) | (bit8_intermmediate_rot << (32 - rotating_amount));
        }

        uint32_t register_input = (instruction >> 16) & 0xF;
        uint32_t register_destination = (instruction >> 12) & 0xF;
    
        switch (opcode)
        {
        case 0x4:
            registers[register_destination] = registers[register_input] + flexible_constant;
            break;
        
        default:
            break;
        }
    
    }

};