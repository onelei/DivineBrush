//
// Created by onelei on 2024/7/8.
//

#include "AudioSource.h"
#include "Audio.h"
#include "../Component/GameObject.h"
#include "../../depends/debug/debug.h"

namespace DivineBrush {
    RTTR_REGISTRATION {
        rttr::registration::class_<AudioSource>("AudioSource")
                .constructor<>()(rttr::policy::ctor::as_raw_ptr);
    }

    AudioSource::AudioSource() {

    }

    AudioSource::~AudioSource() {
        alDeleteSources(1, &source);
        alDeleteBuffers(1, &buffer);
        Audio::RemoveAudioSource(this);
    }

    void AudioSource::SetClip(AudioClip *clip) {
        alGenBuffers(1, &buffer);
        AudioClip::CheckError("Failed to generate OpenAL buffer");

        alBufferData(buffer, clip->GetFormat(), clip->GetSamples().data(),
                     clip->GetSamples().size() * sizeof(short), clip->GetSampleRate());
        AudioClip::CheckError("Failed to buffer data");

        alSourcei(source, AL_BUFFER, buffer);
        audioClip = clip;
    }

    void AudioSource::Play() {
        alSourcePlay(source);
        isStopped = false;
    }

    void AudioSource::Stop() {
        alSourceStop(source);
        isStopped = true;
    }

    void AudioSource::Pause() {
        alSourcePause(source);
    }

    void AudioSource::Resume() {
        alSourcePlay(source);
    }

    void AudioSource::OnThreadUpdate() {
        if (isStopped)
            return;
        if (audioClip == nullptr)
            return;
        ALint state;
        alGetSourcei(source, AL_SOURCE_STATE, &state);
        switch (state) {
            case AL_PLAYING:
                //std::cout << "AudioSource is playing." << std::endl;
                break;
            case AL_PAUSED:
                //std::cout << "AudioSource is paused." << std::endl;
                break;
            case AL_STOPPED:
                Debug::Log("AudioSource is stopped.");
                isStopped = true;
                break;
            case AL_INITIAL:
                //std::cout << "AudioSource is in initial state." << std::endl;
                break;
            default:
                std::cerr << "AudioSource state is unknown: " << state << std::endl;
                break;
        }
    }

    void AudioSource::OnAwake() {
        Component::OnAwake();
        alGenSources(1, &source);
        AudioClip::CheckError("Failed to generate OpenAL source");

        alSourcef(source, AL_GAIN, gain);
        alSourcef(source, AL_PITCH, pitch);
        alSourcei(source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
        auto position = GetGameObject()->GetTransform()->GetPosition();
        lastPosition = position;
        alSource3f(source, AL_POSITION, position.x, position.y, position.z);
        Audio::AddAudioSource(this);
    }

    void AudioSource::OnStart() {
        Component::OnStart();
        Play();
    }

    void AudioSource::OnUpdate() {
        Component::OnUpdate();
        auto position = GetGameObject()->GetTransform()->GetPosition();
        if (lastPosition != position) {
            lastPosition = position;
            alSource3f(source, AL_POSITION, position.x, position.y, position.z);
        }
    }

} // DivineBrush