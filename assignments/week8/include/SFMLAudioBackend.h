#ifndef SFML_AUDIO_BACKEND
#define SFML_AUDIO_BACKEND

#include <SFML/Audio.hpp>
#include "IAudioBackend.h"

class SFMLAudioBackend : public IAudioBackend {

private:

    sf::Music music;
    bool isPlaying = false;

public:

    bool load(const std::string& filePath) override;
    void play() override;
    void pause() override;
    void stop() override;

};

#endif