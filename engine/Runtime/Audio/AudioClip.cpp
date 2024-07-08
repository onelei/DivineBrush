//
// Created by onelei on 2024/7/8.
//

#include "AudioClip.h"
#include "../../depends/debug/debug.h"
#include "../Application.h"
#include <thread>
#include <stdexcept>
#include <filesystem>

namespace DivineBrush {
    AudioClip::AudioClip(const std::string &filename) {
        auto path = Application::GetDataPath() + filename;
        if (!std::filesystem::exists(path)){
            Debug::LogError("AudioClip::AudioClip file not found: " + path);
            return;
        }
        // Load file
        SF_INFO sfInfo;
        SNDFILE *sndFile = sf_open(path.c_str(), SFM_READ, &sfInfo);
        if (!sndFile) {
            Debug::LogError("Failed to open file: "+ path);
            return;
        }

        // Read file data
        samples.resize(sfInfo.frames * sfInfo.channels);
        sf_read_short(sndFile, samples.data(), samples.size());
        sf_close(sndFile);

        // Determine format
        if (sfInfo.channels == 1) {
            format = AL_FORMAT_MONO16;
        } else if (sfInfo.channels == 2) {
            format = AL_FORMAT_STEREO16;
        } else {
            throw std::runtime_error("Unsupported channel count: " + std::to_string(sfInfo.channels));
        }

        sampleRate = sfInfo.samplerate;
    }

    void AudioClip::CheckError(const std::string &message) {
        ALenum error = alGetError();
        if (error != AL_NO_ERROR) {
            std::cerr << message << " - OpenAL error: " << error << std::endl;
            Debug::LogError("OpenAL error: " + message);
            exit(EXIT_FAILURE);
        }
    }
} // DivineBrush