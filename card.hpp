#ifndef CARD_H
#define CARD_H

#include <alsa/asoundlib.h>
#include <iostream>
#include <string>

/**
 * Cards in ALSA are a representation of your audio hardware
 */
class Card {
private:
    int index;
    std::string name;
    std::string long_name;
    snd_ctl_t* ctl_handle;
    snd_pcm_info_t* pcm_info;
public:
    Card(int card_index);

    friend std::ostream& operator<<(std::ostream& os, const Card& card);
};

#endif