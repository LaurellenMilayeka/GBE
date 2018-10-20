#pragma once

#include "GBE.hpp"

namespace GBE {

    class Input {

        private:

            static Byte _buttonInputs;
            static Byte _directionInputs;

        public:

            static bool Update();
            static Byte GetButtonInputs();
            static Byte GetDirectionInputs();

    };

};