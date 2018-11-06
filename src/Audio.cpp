#include "Audio.hpp"

using namespace GBE;

Gb_Apu *Audio::_apu = nullptr;
Stereo_Buffer *Audio::_buffer = nullptr;
int Audio::_elapsedCycles = 0;
int Audio::_sampleRate = 44100;
blip_sample_t *Audio::_sampleBuffer = nullptr;
Sound_Queue Audio::sound;

void Audio::Init() {
    Audio::_sampleBuffer = new blip_sample_t[8192];
    Audio::_apu = new Gb_Apu();
    Audio::_buffer = new Stereo_Buffer();
    Audio::_buffer->clock_rate(4194304);
    Audio::_buffer->set_sample_rate(44100);
    Audio::_apu->treble_eq(0);
    Audio::_buffer->bass_freq(0);
    Audio::_apu->output(Audio::_buffer->center(), Audio::_buffer->left(), Audio::_buffer->right());
    Audio::sound.start(Audio::_sampleRate, 2);
}

void Audio::SetSampleRate(int sampleRate) {
    if (sampleRate != Audio::_sampleRate) {
        Audio::_sampleRate = sampleRate;
        Audio::_buffer->set_sample_rate(sampleRate);
    }
}

void Audio::EndFrame(int elapsedCycles)
{
	bool stereo = Audio::_apu->end_frame(elapsedCycles);
	Audio::_buffer->end_frame(elapsedCycles, stereo);
	
	if (Audio::_buffer->samples_avail() >= 8192) {
	    size_t count = Audio::_buffer->read_samples(Audio::_sampleBuffer, 8192);
		sound.write(Audio::_sampleBuffer, count);
    }
}


Gb_Apu *Audio::GetAPU() {
    return (Audio::_apu);
}

Stereo_Buffer *Audio::GetBuffer() {
    return (Audio::_buffer);
}

blip_sample_t *Audio::GetSampleBuffer() {
    return (Audio::_sampleBuffer);
}