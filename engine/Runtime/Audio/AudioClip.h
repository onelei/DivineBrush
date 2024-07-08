//
// Created by onelei on 2024/7/8.
//

#ifndef ENGINE_AUDIOCLIP_H
#define ENGINE_AUDIOCLIP_H

#include <string>
#include <vector>
#include <AL/al.h>
#include <iostream>
#include <sndfile.h>

namespace DivineBrush {

    class AudioClip {
    public:
        AudioClip(const std::string &filename);

        ~AudioClip();

        static void CheckError(const std::string &message);

        ALenum GetFormat() const { return format; }

        ALsizei GetSampleRate() const { return sampleRate; }

        const std::vector<short> &GetSamples() const { return samples; }

    private:
        ALenum format;
        ALsizei sampleRate;
        std::vector<short> samples;
    };

} // DivineBrush

#endif //ENGINE_AUDIOCLIP_H
