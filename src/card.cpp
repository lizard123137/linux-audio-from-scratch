#include "card.hpp"

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