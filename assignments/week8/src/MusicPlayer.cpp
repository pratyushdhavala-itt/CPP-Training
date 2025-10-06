#include <string>
#include <SFML/Audio.hpp>
#include "MusicPlayer.h"
#include "Playlist.h"
#include "Song.h"

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
    currentSong = &currentPlaylist->getCurrentSong();
    backendPlayer->load(currentSong->getFilePath());
    backendPlayer->play();
}

void MusicPlayer::pause() {
    backendPlayer->pause();
}

void MusicPlayer::stop() {
    backendPlayer->stop();
}

void MusicPlayer::next() {
    currentPlaylist->nextSong();
    play();
}

void MusicPlayer::previous() {
    currentPlaylist->previousSong();
    play();
}