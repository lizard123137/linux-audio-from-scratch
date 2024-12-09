#include <iostream>
#include <vector>

#include "alsa_manager.hpp"
#include "device.hpp"
#include "wav_file.hpp"

int main(void) {
    std::cout << "Using Alsa version: " << AlsaManager::getAlsaVersion() << std::endl;

    auto devices = AlsaManager::getAudioCards();

    for (auto dev : devices) {
        std::cout << dev << std::endl;
    }

    // Somehow leaks memory - all the leaks trace back to snd_pcm_open???
    //auto device = AlsaManager::getDevice("default");
    //device.Configure();

    // Wav file testing
    WavFile file("./sample.wav");
    std::cout << file << std::endl;
}