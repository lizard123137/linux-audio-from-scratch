#include "audio_manager.hpp"

std::vector<Card> AudioManager::getAudioCards() {
    int card_index = -1;

    std::vector<Card> devices = {};

    while (snd_card_next(&card_index) >= 0 && card_index >= 0) {
        devices.push_back(Card(card_index));
    }

    return devices;
}