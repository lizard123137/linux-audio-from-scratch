#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "card.hpp"

#include <alsa/asoundlib.h>
#include <vector>

class AudioManager {
private:
    AudioManager();
public:
    static std::vector<Card> getAudioCards();
};

#endif