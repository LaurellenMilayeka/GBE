//
// Created by Flox Ajuro on 08/09/2018.
//

#ifndef GAMEBOY_EMULATOR_LOADER_HPP
#define GAMEBOY_EMULATOR_LOADER_HPP

#include <string>
#include <cstring>

namespace GBE {

    class Loader {

        public:

            static void LoadBootloader();
            static void LoadROM(std::string const& romPath);
            static void UnloadROM();

    };

};

#endif //GAMEBOY_EMULATOR_LOADER_HPP
