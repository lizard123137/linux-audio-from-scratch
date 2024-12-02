#include "card.hpp"

Card::Card(int card_index) {
    this->index = card_index;

    char* name_tmp = nullptr;
    char* long_name_tmp = nullptr;
    
    snd_card_get_name(card_index, &name_tmp);
    snd_card_get_longname(card_index, &long_name_tmp);

    this->name = name_tmp;
    this->long_name = long_name_tmp;
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << "Card {\n" 
        << "\tindex = " << card.index << ",\n"
        << "\tname = " << card.name << ",\n"
        << "\tlong_name = " << card.long_name << "\n"
        << "}\n";
    return os;
}