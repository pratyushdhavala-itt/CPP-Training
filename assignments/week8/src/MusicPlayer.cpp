#include <string>
#include <SFML/Audio.hpp>
#include "MusicPlayer.h"
#include "Playlist.h"
#include "Song.h"
#include "MusicPlayerException.h"

MusicPlayer::MusicPlayer(IAudioBackend* backendPlayer)
    : backendPlayer{backendPlayer}, currentSong{nullptr} {}

void MusicPlayer::loadPlaylist(Playlist& playlist) {

    currentPlaylist = &playlist;
}

Playlist* MusicPlayer::getLoadedPlaylist() const {
    return currentPlaylist;
}

const Song& MusicPlayer::getCurrentSong() {
    return *this->currentSong;
}

void MusicPlayer::play() {
    if (currentSong == nullptr) {
        currentSong = &currentPlaylist->getCurrentSong();
        backendPlayer->load(currentSong->getFilePath());
    }
    backendPlayer->play();
}

void MusicPlayer::pause() {
    try {
        backendPlayer->pause();
    } catch (const MusicPlayerException& m) {
        throw;
    }
}

void MusicPlayer::stop() {
    backendPlayer->stop();
}

void MusicPlayer::next() {
    currentPlaylist->nextSong();
    currentSong = nullptr;
    play();
}

void MusicPlayer::previous() {
    currentPlaylist->previousSong();
    currentSong = nullptr;
    play();
}