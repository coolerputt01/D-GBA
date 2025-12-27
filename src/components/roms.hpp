#pragma once
#include <string>
#include <cstdint>
#include <vector>
#include <fstream>
#include <iostream>
#include "../config/config.hpp"

struct Rom {
    std::vector<uint8_t> rom_data;

    bool load(const char* path = TEST_ROM){
        std::ifstream file(path,std::ios::binary | std::ios::ate);

        if(!file.is_open()){
            std::cerr<<"An error occured while opening ROMs\n";
            return false;
        }

        std::streamsize fileBitSize = file.tellg();
        file.seekg(0,std::ios::beg);
        rom_data.resize(fileBitSize);

        if(!file.read(static_cast<char *>(static_cast<void*>(rom_data.data())),fileBitSize)){
            std::cerr << "An error occured while reading from file to buffer\n";
            return false;
        }

        std::cout<<"Rom sucessfully loaded\n"<<"Bits: "<<fileBitSize<<std::endl;
        return true;

    }
};