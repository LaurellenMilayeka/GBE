#pragma once

#include "GBE.hpp"

#include "gb_apu/Gb_Apu.h"
#include "gb_apu/Multi_Buffer.h"
#include "gb_apu/Sound_Queue.h"

namespace GBE {

    class Audio {

        private:

            static Gb_Apu *_apu;
            static Stereo_Buffer *_buffer;
            static int _elapsedCycles;
            static int _sampleRate;
            static blip_sample_t *_sampleBuffer;
            static Sound_Queue sound;

        public:

            static void Init();

            static void SetSampleRate(int sampleRate);
            static void EndFrame(int elapsedCycles);

            static Gb_Apu *GetAPU();
            static Stereo_Buffer *GetBuffer();
            static blip_sample_t *GetSampleBuffer();

    };

};