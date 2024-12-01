#include <cmath>
#include <iostream>
#include <alsa/asoundlib.h>

/**
 * This is a bit annoying, but it's less annoying than trying to debug it without errors
 */
void error_check(int code) {
    if (code < 0) {
        std::cout << "Issue encountered: " << snd_strerror(code) << std::endl;
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    /* Get handle to audio device - use aplay -l to list your devices */
    snd_pcm_t* handle;
    error_check(snd_pcm_open(&handle, "hw:1,3", SND_PCM_STREAM_PLAYBACK, 0));


    /* Allocate space for params */
    snd_pcm_hw_params_t* params;
    error_check(snd_pcm_hw_params_malloc(&params));

    /**
     * Params are used to configure the device settings,
     * most of the functions describe exactly, which aspect they are configuring.
     * 
     * For a bit more context here are the things i thought needed an explanation
     * snd_pcm_hw_params_any - set the params to some reasonable defaults
     * snd_pcm_hw_params_set_access - tells device where to store samples buffer/memory-mapped i/o (technical stuff...)
     */
    error_check(snd_pcm_hw_params_any(handle, params));
    error_check(snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED));

    /* Little Endian format */
    error_check(snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE));
    
    /* Sample rate */
    unsigned int rate = 44100;
    error_check(snd_pcm_hw_params_set_rate_near(handle, params, &rate, 0));
    
    /* Stereo */
    error_check(snd_pcm_hw_params_set_channels(handle, params, 2));

    /* Apply the parameters */
    error_check(snd_pcm_hw_params(handle, params));

    /* Free them */
    snd_pcm_hw_params_free(params);

    /* Finally play the my chemical romance G note */
    const double frequency = 392.0; /* G4 note at 392 Hz*/
    const double amplitude = 32767.0;
    const int num_samples = 128;
    short buf[num_samples * 2]; /* Twice the samples since we are in stereo */

    double phase = 0.0;
    const double phase_inc = (2.0 * M_PI * frequency) / rate;

    int iter = (rate * 2) / num_samples;
    for(int i = 0; i < iter; i++) {
        for (int j = 0; j < num_samples; j++) {
            short sample = static_cast<short>(amplitude * sin(phase));;
            
            buf[j * 2] = sample;
            buf[j * 2 + 1] = sample;
            
            phase += phase_inc;

            if (phase >= 2.0 * M_PI)
                phase = 0.0;
        }
    }

    error_check(snd_pcm_writei(handle, buf, num_samples));

    snd_pcm_close(handle);
    return EXIT_SUCCESS;
}