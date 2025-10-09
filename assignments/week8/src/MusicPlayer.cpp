#include <string>
#include <SFML/Audio.hpp>
#include "MusicPlayer.h"
#include "Playlist.h"
#include "Song.h"
#include "MusicPlayerException.h"

MusicPlayer::MusicPlayer(IAudioPlayer* audioPlayer)
    : audioPlayer{audioPlayer}, currentSong{nullptr} {}

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
        audioPlayer->load(currentSong->getFilePath());
    }
    try {
        audioPlayer->play();
    } catch (const MusicPlayerException& m) {
        throw;
    }
}

void MusicPlayer::pause() {
    try {
        audioPlayer->pause();
    } catch (const MusicPlayerException& m) {
        throw;
    }
}

void MusicPlayer::stop() {
    try {
        audioPlayer->stop();
    } catch (const MusicPlayerException& m) {
        throw;
    }
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