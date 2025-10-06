
#include "SFMLAudioBackend.h"

bool SFMLAudioBackend::load(const std::string& filePath) {
    return music.openFromFile(filePath);
}

void SFMLAudioBackend::play() {
    music.play();
}

void SFMLAudioBackend::pause() {
    music.pause();
}

void SFMLAudioBackend::stop() {
    music.stop();
}