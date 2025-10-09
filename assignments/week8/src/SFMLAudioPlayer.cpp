#include "MusicPlayerException.h"
#include "SFMLAudioPlayer.h"

bool SFMLAudioPlayer::load(const std::string& filePath) {
    return music.openFromFile(filePath);
}

void SFMLAudioPlayer::play() {
    music.play();
    if (music.getStatus() != sf::SoundSource::Status::Playing) {
        throw MusicPlayerException("Backend failure ! ! ! Try again later ! ! !");
    }
}

void SFMLAudioPlayer::pause() {
    if (music.getStatus() != sf::SoundSource::Status::Playing) {
        throw MusicPlayerException("No song playing ! ! !");
    }
    music.pause();
}

void SFMLAudioPlayer::stop() {
    music.stop();
}