//
// Created by Flox Ajuro on 08/09/2018.
//

#ifndef GAMEBOY_EMULATOR_ROM_HPP
#define GAMEBOY_EMULATOR_ROM_HPP

#include <string>

#include "GBE.hpp"

namespace GBE {

    class ROM {

        private:

        public:

            static std::string name;
            static unsigned int size;

            static Byte first256[256];
    };

};

#endif //GAMEBOY_EMULATOR_ROM_HPP
