#ifndef CARD_H
#define CARD_H

#include "exceptions/alsa_exception.hpp"

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

Card::Card(int card_index) {
    this->index = card_index;

    char* name_tmp = nullptr;
    char* long_name_tmp = nullptr;
    
    int err;

    err = snd_card_get_name(card_index, &name_tmp);
    if (err < 0)
        throw AlsaException(err);

    err = snd_card_get_longname(card_index, &long_name_tmp);
    if (err < 0)
        throw AlsaException(err);

    this->name = name_tmp;
    this->long_name = long_name_tmp;

    free(name_tmp);
    free(long_name_tmp);
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << "Card {\n" 
        << "\tindex = " << card.index << ",\n"
        << "\tname = " << card.name << ",\n"
        << "\tlong_name = " << card.long_name << "\n"
        << "}\n";
    return os;
}

#endif