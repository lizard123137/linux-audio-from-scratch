#ifndef GENERATOR_H
#define GENERATOR_H

#include <cstdint>
#include <cstdlib>
#include <cmath>

/**
 * The returned data is supposed to be in little endian form,
 * but for now it doesn't matter since we are using 8-bits per sample
 */
class Generator {
public:
    static uint8_t* generateSine(uint32_t rate, uint8_t channels, uint32_t length, uint32_t frequency);
};

uint8_t* Generator::generateSine(uint32_t rate, uint8_t channels, uint32_t length, uint32_t frequency) {
    uint64_t bytes = rate * channels * length;
    uint8_t* data = (uint8_t*)malloc(bytes);

    for(uint64_t i = 0; i < rate * length; ++i) {
        // TODO find function to generate the right frequency
        uint8_t value = (sin(i / frequency) + 1.0) / 2.0 * 255.0;

        for(uint8_t channel = 0; channel < channels; ++channel) {
            data[i + channel] = value;
        }
    }

    return data;
}

#endif