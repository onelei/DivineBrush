//
// Created by onelei on 2024/3/29.
//

#include "Audio.h"
#include <iostream>

namespace DivineBrush {
    std::unordered_set<AudioSource *> Audio::sources;
    std::thread Audio::audioThread;
    std::mutex Audio::mutex;
    bool Audio::exitFlag = false;
    ALCdevice *Audio::device = nullptr;
    ALCcontext *Audio::context = nullptr;

    void Audio::Init() {
        audioThread = std::thread(&Audio::Update);
    }

    void Audio::Update() {
        // 初始化OpenAL设备和上下文
        device = alcOpenDevice(nullptr);
        if (!device) {
            std::cerr << "Failed to open audio device" << std::endl;
            return;
        }
        context = alcCreateContext(device, nullptr);
        if (!alcMakeContextCurrent(context)) {
            std::cerr << "Failed to set audio context" << std::endl;
            return;
        }
        while (true) {
            if (exitFlag) {
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            //std::unique_lock<std::mutex> lock(mutex);
            //cv.wait_for(lock, std::chrono::milliseconds(100), [this] { return exitFlag; });
            for (auto source: sources) {
                source->OnThreadUpdate();
            }
        }
    }

    void Audio::AddAudioSource(AudioSource *source) {
        std::lock_guard<std::mutex> lock(mutex);
        sources.insert(source);
    }

    void Audio::RemoveAudioSource(AudioSource *source) {
        std::lock_guard<std::mutex> lock(mutex);
        sources.erase(source);
    }

    void Audio::Destroy() {
        std::lock_guard<std::mutex> lock(mutex);
        exitFlag = true;
        audioThread.join();

        alcMakeContextCurrent(nullptr);
        alcDestroyContext(context);
        alcCloseDevice(device);
    }

} // DivineBrush