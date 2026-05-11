#pragma once

#include "ecs/entity.h"
#include <string>

namespace lumin {

/**
 * AudioSource Component - plays sound effects and music
 */
class AudioSource : public Component {
public:
    AudioSource();

    bool loadAudio(const std::string& path);
    
    void play();
    void pause();
    void stop();
    void resume();

    void setVolume(float volume);
    void setPitch(float pitch);
    void setLoop(bool loop);

    float getVolume() const { return volume_; }
    float getPitch() const { return pitch_; }
    bool getLoop() const { return loop_; }
    bool isPlaying() const { return isPlaying_; }

private:
    std::string audioPath_;
    float volume_;
    float pitch_;
    bool loop_;
    bool isPlaying_;
    uint32_t audioID_;
};

} // namespace lumin
