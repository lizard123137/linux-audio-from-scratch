#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "exceptions/alsa_exception.hpp"
#include "card.hpp"
#include "device.hpp"

#include <alsa/asoundlib.h>
#include <string>
#include <vector>

class AlsaManager {
private:
    AlsaManager();
public:
    static std::string getAlsaVersion();
    static std::vector<Card> getAudioCards();
    static Device getDevice(std::string name, bool output = true, int mode = 0);
};

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

#endif