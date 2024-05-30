//
// Created by onelei on 2024/3/29.
//

#include "Audio.h"
#include <iostream>
#include <fstream>
#include "../../Runtime/Application.h"

namespace DivineBrush {
    bool Audio::isInit = false;

    void Audio::Init() {
        if (isInit)
            return;
        // 初始化OpenAL设备和上下文
        ALCdevice *device = alcOpenDevice(nullptr);
        if (!device) {
            std::cerr << "Failed to open audio device" << std::endl;
            return;
        }
        ALCcontext *context = alcCreateContext(device, nullptr);
        if (!alcMakeContextCurrent(context)) {
            std::cerr << "Failed to set audio context" << std::endl;
            return;
        }
        isInit = true;
    }

    std::vector<char> Audio::LoadWAV(const std::string &filename, ALenum &format, ALsizei &freq) {
        std::ifstream file(Application::GetDataPath() + filename, std::ios::binary);
        if (!file) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return {};
        }

        // Read the header
        char buffer[44];
        file.read(buffer, 44);

        // Check the file format
        if (std::string(buffer, 4) != "RIFF" || std::string(buffer + 8, 4) != "WAVE") {
            std::cerr << "Invalid WAV file format: " << filename << std::endl;
            return {};
        }

        // Extract format and frequency
        format = (buffer[22] == 1 && buffer[34] == 16) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
        freq = *reinterpret_cast<int *>(buffer + 24);

        // Read the data
        int dataSize = *reinterpret_cast<int *>(buffer + 40);
        std::vector<char> data(dataSize);
        file.read(data.data(), dataSize);

        return data;
    }

    void Audio::Play2D(const std::string &filename) {
        // 初始化OpenAL设备和上下文
        ALCdevice *device = alcOpenDevice(nullptr);
        if (!device) {
            std::cerr << "Failed to open audio device" << std::endl;
            return;
        }

        ALCcontext *context = alcCreateContext(device, nullptr);
        if (!alcMakeContextCurrent(context)) {
            std::cerr << "Failed to set audio context" << std::endl;
            return;
        }

        // 创建背景音乐Buffer和Source
//        ALuint bgmBuffer;
//        alGenBuffers(1, &bgmBuffer);
//        CheckError("buffer generation");
//
//        ALenum bgmFormat;
//        ALsizei bgmFreq;
//        std::Vector<char> bgmData = LoadWAV("audio/background_music.wav", bgmFormat, bgmFreq);
//        alBufferData(bgmBuffer, bgmFormat, bgmData.data(), bgmData.size(), bgmFreq);
//        CheckError("buffer data");
//
//        ALuint bgmSource;
//        alGenSources(1, &bgmSource);
//        CheckError("source generation");
//
//        alSourcei(bgmSource, AL_BUFFER, bgmBuffer);
//        CheckError("source buffer");
//
//        alSourcei(bgmSource, AL_LOOPING, AL_TRUE); // 循环播放背景音乐
//        alSourcePlay(bgmSource);
//        CheckError("source play");

        // 创建音效Buffer和Source
        ALuint sfxBuffer;
        alGenBuffers(1, &sfxBuffer);
        ALenum sfxFormat;
        ALsizei sfxFreq;
        std::vector<char> sfxData = LoadWAV("audio/sound_effect.wav", sfxFormat, sfxFreq);
        alBufferData(sfxBuffer, sfxFormat, sfxData.data(), sfxData.size(), sfxFreq);

        ALuint sfxSource;
        alGenSources(1, &sfxSource);
        alSourcei(sfxSource, AL_BUFFER, sfxBuffer);
        alSourcei(sfxSource, AL_LOOPING, AL_FALSE); // 不循环播放音效

        // 播放音效
        alSourcePlay(sfxSource);

        // 等待音效播放结束
        ALint state;
        do {
            alGetSourcei(sfxSource, AL_SOURCE_STATE, &state);
        } while (state == AL_PLAYING);

        // 清理资源
        alDeleteSources(1, &sfxSource);
        alDeleteBuffers(1, &sfxBuffer);
        // alDeleteSources(1, &bgmSource);
        // alDeleteBuffers(1, &bgmBuffer);
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(context);
        alcCloseDevice(device);
    }

    void Audio::Play3D(const std::string &filename, glm::vec3 pos) {
        ALCdevice *device = alcOpenDevice(nullptr);
        if (!device) {
            std::cerr << "Failed to open audio device" << std::endl;
            return;
        }

        ALCcontext *context = alcCreateContext(device, nullptr);
        if (!alcMakeContextCurrent(context)) {
            std::cerr << "Failed to set audio context" << std::endl;
            return;
        }

        ALuint buffer;
        alGenBuffers(1, &buffer);

        ALenum format;
        ALsizei freq;
        std::vector<char> data = LoadWAV(filename, format, freq);
        alBufferData(buffer, format, data.data(), data.size(), freq);

        ALuint source;
        alGenSources(1, &source);
        alSourcei(source, AL_BUFFER, buffer);

        // Set the source position for 3D sound
        alSource3f(source, AL_POSITION, pos.x, pos.y, pos.z); // Position the source 5 units away on the Z-axis

        alSourcePlay(source);

        // Wait for the audio to finish
        ALint state;
        do {
            alGetSourcei(source, AL_SOURCE_STATE, &state);
        } while (state == AL_PLAYING);

        alDeleteSources(1, &source);
        alDeleteBuffers(1, &buffer);
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(context);
        alcCloseDevice(device);

    }

    void Audio::Play(ALuint sfxSource) {
        // 播放音效
        alSourcePlay(sfxSource);
    }

    void Audio::Pause(ALuint sfxSource) {
        // 暂停音效
        std::cout << "Pausing sound effect..." << std::endl;
        alSourcePause(sfxSource);
    }

    void Audio::Resume(ALuint sfxSource) {
        // 恢复音效播放
        std::cout << "Resuming sound effect..." << std::endl;
        alSourcePlay(sfxSource);
    }

    void Audio::Stop(ALuint sfxSource) {
        // 停止音效
        std::cout << "Stopping sound effect..." << std::endl;
        alSourceStop(sfxSource);
    }

    void Audio::Clear(ALuint sfxSource) {
        // 清理资源
        alDeleteSources(1, &sfxSource);
        //alDeleteBuffers(1, &sfxBuffer);
    }

    void Audio::ClearAll() {

    }

    void Audio::CheckError(const char *operation) {
        ALenum error = alGetError();
        if (error != AL_NO_ERROR) {
            fprintf(stderr, "OpenAL error during %s: %s\n", operation, alGetString(error));
            exit(EXIT_FAILURE);
        }
    }

} // DivineBrush