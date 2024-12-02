#include <iostream>
#include <vector>

#include "audio_manager.hpp"

int main(void) {
    auto devices = AudioManager::getAudioCards();

    for (auto dev : devices) {
        std::cout << dev << std::endl;
    }
}