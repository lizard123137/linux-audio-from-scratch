#include "device.hpp"

Device::Device(std::string name, bool output, int mode) {
    this->name = name;
    this->handle = nullptr;

    snd_pcm_stream_t stream = output ? SND_PCM_STREAM_PLAYBACK : SND_PCM_STREAM_CAPTURE;

    int err;

    err = snd_pcm_open(&this->handle, name.c_str(), stream, mode);
    if (err < 0) throw AlsaException(err);

    snd_pcm_hw_params_malloc(&this->params);
    snd_pcm_hw_params_any(this->handle, this->params);
}

Device::~Device() {
    if (this->params) {
        snd_pcm_hw_params_free(this->params);
        this->params = nullptr;
    }

    if (this->handle) {
        snd_pcm_drain(this->handle);
        snd_pcm_close(this->handle);
        this->handle = nullptr;
    }
}

void Device::Configure(unsigned int rate, bool stereo, bool interleaved) {
    int err;

    // Couple sanity checks
    if (!this->handle)
        throw std::runtime_error("PCM handle is uninitialized");
    if (!this->params)
        throw std::runtime_error("Params are uninitialized");
    if (snd_pcm_state(this->handle) != SND_PCM_STATE_OPEN)
        throw std::runtime_error("PCM device is not in a valid state");

    err = snd_pcm_hw_params_set_access(this->handle, this->params, interleaved ? SND_PCM_ACCESS_RW_INTERLEAVED : SND_PCM_ACCESS_RW_NONINTERLEAVED);
    if (err < 0) throw AlsaException(err);

    err = snd_pcm_hw_params_set_channels(this->handle, this->params, stereo ? 2 : 1);
    if (err < 0) throw AlsaException(err);

    err = snd_pcm_hw_params_set_rate(this->handle, this->params, rate, NULL);
    if (err < 0) throw AlsaException(err);

    err = snd_pcm_hw_params_set_format(this->handle, this->params, SND_PCM_FORMAT_S16_LE);
    if (err < 0) throw AlsaException(err);

    err = snd_pcm_hw_params(this->handle, this->params);
    if (err < 0) throw AlsaException(err);
}
    
void Device::PlayPCM(void* data, long length) {
    // Couple sanity checks
    if (!this->handle)
        throw std::runtime_error("PCM handle is uninitialized");
    if (!this->params)
        throw std::runtime_error("Params are uninitialized");

    // For now lets assume that the user configured the PCM device
    // TODO configure device instead of assuming or at least check if it's configured correctly
    unsigned int channels;
    snd_pcm_hw_params_get_channels(this->params, &channels);

    snd_pcm_uframes_t frames;
    snd_pcm_hw_params_get_period_size(this->params, &frames, 0);

    // TODO replace 44100 with actual sample rate
    snd_pcm_writei(this->handle, data, 44100);
}