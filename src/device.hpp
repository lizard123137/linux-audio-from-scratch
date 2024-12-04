#ifndef DEVICE_H
#define DEVICE_H

#include "exceptions/alsa_exception.hpp"

#include <alsa/asoundlib.h>
#include <stdexcept>
#include <string>

class Device {
private:
    std::string name;
    snd_pcm_t* handle;
    snd_pcm_hw_params_t* params;
public:
    Device(std::string name, bool output = true, int mode = 0);
    virtual ~Device();
    void Configure(unsigned int rate = 44100, bool stereo = true, bool interleaved = true);
};

#endif