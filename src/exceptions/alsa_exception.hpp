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

#endif