#pragma once

#include <memory>
#include <string>

namespace lumin {

/**
 * Audio Engine - manages audio playback and effects
 */
class AudioEngine {
public:
    AudioEngine();
    ~AudioEngine();

    bool initialize();
    void shutdown();

    void update(float deltaTime);

    // Master volume control
    void setMasterVolume(float volume);
    float getMasterVolume() const { return masterVolume_; }

    // Audio playback
    uint32_t playSound(const std::string& path, float volume = 1.0f, bool loop = false);
    void stopSound(uint32_t soundID);
    void pauseSound(uint32_t soundID);
    void resumeSound(uint32_t soundID);

private:
    float masterVolume_;
    void* audioDevice_;  // ALCdevice*
    void* audioContext_; // ALCcontext*
};

} // namespace lumin
