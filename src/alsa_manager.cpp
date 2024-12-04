#include "alsa_manager.hpp"

std::string AlsaManager::getAlsaVersion() {
    return SND_LIB_VERSION_STR;
}

std::vector<Card> AlsaManager::getAudioCards() {
    int card_index = -1;

    std::vector<Card> devices = {};

    while (snd_card_next(&card_index) >= 0 && card_index >= 0) {
        devices.push_back(Card(card_index));
    }

    return devices;
}

Device AlsaManager::getDevice(std::string name, bool output, int mode) {
    return Device(name, output, mode);
}