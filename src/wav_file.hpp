#ifndef WAV_DECODER_H
#define WAV_DECORED_H

#include <cstdint>
#include <cstdio>
#include <fstream>
#include <string>
#include <stdexcept>

/**
 * A WAV file is essentially just Pulse Code Modulation data with a header.
 * It seems that a simple way of decoding it would be to just read in the first 44 bytes,
 * that's our header, afterwards all that's left is out PCM data.
 * 
 * I am assuming that we're using a little endian system...
 * I feel like thats a fair assumption...
 * I am not planning any support for motorola CPUs after all...
 */
class WavFile {
private:
    uint16_t audio_format;      // offset 20 - indicates if we used compression
    uint16_t num_channels;      // offset 22
    uint32_t sample_rate;       // offset 24
    uint16_t bits_per_sample;   // offset 34
public:
    WavFile(std::string path);

    uint16_t getAudioFormat() const;
    uint16_t getNumChannels() const;
    uint32_t getSampleRate() const;
    uint16_t getBitsPerSample() const;
};

WavFile::WavFile(std::string path) {
    FILE* file = fopen(path.c_str(), "r");

    if (file == nullptr) {
        throw std::runtime_error("Failed to open file: " + path);
    }

    fseek(file, 20, SEEK_SET);
    fread(&this->audio_format, sizeof(this->audio_format), 1, file);

    fseek(file, 22, SEEK_SET);
    fread(&this->num_channels, sizeof(this->num_channels), 1, file);

    fseek(file, 24, SEEK_SET);
    fread(&this->sample_rate, sizeof(this->sample_rate), 1, file);

    fseek(file, 34, SEEK_SET);
    fread(&this->bits_per_sample, sizeof(this->bits_per_sample), 1, file);

    // TODO parse the actual PCM data

    fclose(file);
}

uint16_t WavFile::getAudioFormat() const {
    return this->audio_format;
}

uint16_t WavFile::getNumChannels() const {
    return this->num_channels;
}

uint32_t WavFile::getSampleRate() const {
    return this->sample_rate;
}

uint16_t WavFile::getBitsPerSample() const {
    return this->bits_per_sample;
}

std::ostream& operator<<(std::ostream& os, const WavFile& file) {
    os << "WAVE_File {\n" 
        << "\taudio_format = " << file.getAudioFormat() << "\n"
        << "\tnum_channels = " << file.getNumChannels() << "\n"
        << "\tsample_rate = " << file.getSampleRate() << "\n"
        << "\tbits_per_sample = " << file.getBitsPerSample() << "\n"
        << "}\n";
    return os;
}

#endif