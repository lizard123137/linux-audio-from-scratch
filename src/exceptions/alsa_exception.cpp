#include "alsa_exception.hpp"

AlsaException::AlsaException(int alsa_err) {
    this->message = snd_strerror(alsa_err);
}

const char* AlsaException::what() {
    return this->message.c_str();
}