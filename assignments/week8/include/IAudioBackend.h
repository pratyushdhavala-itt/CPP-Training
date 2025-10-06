#ifndef I_AUDIO_BACKEND_H
#define I_AUDIO_BACKEND_H

#include <string>

class IAudioBackend {

public:

    virtual ~IAudioBackend() = default;

    virtual bool load(const std::string& filePath) = 0;
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
};

#endif