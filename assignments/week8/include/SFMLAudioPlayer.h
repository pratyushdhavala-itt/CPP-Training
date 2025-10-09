#ifndef SFML_AUDIO_PLAYER
#define SFML_AUDIO_PLAYER

#include <SFML/Audio.hpp>
#include "IAudioPlayer.h"

class SFMLAudioPlayer : public IAudioPlayer {

private:

    sf::Music music;

public:

    bool load(const std::string& filePath) override;
    void play() override;
    void pause() override;
    void stop() override;

};

#endif