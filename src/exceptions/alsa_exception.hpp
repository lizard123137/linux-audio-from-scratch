#ifndef ALSA_EXCEPTION_H
#define ALSA_EXCEPTION_H

#include <alsa/asoundlib.h>
#include <string>
#include <exception>

class AlsaException : public std::exception {
private:
    std::string message;
public:
    AlsaException(int alsa_err);
    const char* what();
};

AlsaException::AlsaException(int alsa_err) {
    this->message = snd_strerror(alsa_err);
}

const char* AlsaException::what() {
    return this->message.c_str();
}

#endif