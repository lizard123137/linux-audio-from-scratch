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

#endif