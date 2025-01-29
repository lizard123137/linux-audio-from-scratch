#include <iostream>
#include <vector>

#include "alsa_manager.hpp"
#include "device.hpp"
#include "wav_file.hpp"
#include "generator.hpp"

int main(void) {
    std::cout << "Using Alsa version: " << AlsaManager::getAlsaVersion() << std::endl;

    auto devices = AlsaManager::getAudioCards();

    for (auto dev : devices) {
        std::cout << dev << std::endl;
    }

    // Somehow leaks memory - all the leaks trace back to snd_pcm_open???
    auto device = AlsaManager::getDevice("default");
    device.Configure(44100, false, true);

    // Wav file testing
    WavFile file("./sample.wav");
    std::cout << file << std::endl;

    device.PlayPCM((void*)file.getData(), file.getDataLen());

    // Generator testing
    // TODO fix demonic sound generator
    uint8_t* data = Generator::generateSine(44100, 1, 1, 200);
    device.PlayPCM((void*)data, 44100);

    return EXIT_SUCCESS;
}