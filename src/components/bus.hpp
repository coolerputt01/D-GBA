#pragma once
#include <vector>
#include <cstdint>
#include "roms.hpp"


class Bus {
    public:
        Rom rom;
        Bus(): ewram_data(256 * 1024),iwram_data(32 * 1024),vram_data(96 * 1024){}
        uint8_t read8(uint32_t address){
            if(address >= 0x02000000 && address <= 0x0203FFFF){
                return ewram_data[address - 0x02000000];
            }else if(address >= 0x03000000 && address <= 0x03007FFF){
                return iwram_data[address - 0x03000000];
            }else if(address >= 0x06000000 && address <= 0x06017FFF){
                return vram_data[address - 0x06000000];
            }else if(address >= 0x08000000){
                if(!rom.rom_data.empty() && rom.rom_state != 0){
                    return rom.rom_data[address - 0x08000000];
                }
            }
            return 0xFF;
        }
        uint16_t read16(uint32_t address){
            uint16_t v8_v16l = static_cast<uint16_t>(read8(address));
            uint16_t v8_v16h = static_cast<uint16_t>(read8(address + 1));

            return v8_v16l | (v8_v16h << 8);
        }
        uint32_t read32(uint32_t address){
            uint32_t v16_v32l = static_cast<uint32_t>(read16(address));
            uint32_t v16_v32h = static_cast<uint32_t>(read16(address + 2));

            return v16_v32l | (v16_v32h << 16);
        
        }

        void write8(uint32_t address, uint8_t w_data){
            if(address >= 0x02000000 && address <= 0x0203FFFF){
                ewram_data[address - 0x02000000] = w_data;
            }else if(address >= 0x03000000 && address <= 0x03007FFF){
                iwram_data[address - 0x03000000]  = w_data;
            }else if(address >= 0x06000000 && address <= 0x06017FFF){
                vram_data[address - 0x06000000]  = w_data;
            }else if(address >= 0x08000000){
                return;
            }
        }
        void write16(uint32_t address, uint16_t w_data){
            uint16_t v8_v16l = w_data & 0xFF;
            uint16_t v8_v16h = (w_data >> 8) & 0xFF;

            write8(address,v8_v16l);
            write8(address + 1,v8_v16h);
        }
        void write32(uint32_t address, uint32_t w_data){
            uint16_t v8_v16le1 = w_data & 0xFF;
            uint16_t v8_v16le2 = (w_data >> 8) & 0xFF;
            uint16_t v8_v16le3 = (w_data >> 16) & 0xFF;
            uint16_t v8_v16le4 = (w_data >> 24) & 0xFF;

            write8(address,v8_v16le1);
            write8(address + 1,v8_v16le2);
            write8(address + 2,v8_v16le3);
            write8(address + 3,v8_v16le4);
        }

        ~Bus() = default;

    private:
        std::vector<uint8_t> ewram_data;
        std::vector<uint8_t> vram_data;
        std::vector<uint8_t> iwram_data;
};