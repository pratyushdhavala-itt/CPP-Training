#include <string>
#include <list>
#include <algorithm>
#include "Playlist.h"
#include "Song.h"
#include "MusicPlayerException.h"
#include "AppendItemToString.h"
#include "constants.h"

Playlist::Playlist(const std::string& playlistName, std::list<Song>& songs) 
    : playlistName{playlistName}, songs{songs} {
    currentSong = this->songs.begin();
}

const std::string& Playlist::getPlaylistName() const {

    return playlistName;
}

const std::list<Song>& Playlist::getAllSongs() const {

    return songs;
}

void Playlist::addSong(const Song& song) {

    std::list<Song>::iterator it = std::find(songs.begin(), songs.end(), song);
    if (it != songs.end()) throw MusicPlayerException(PRINT_SONG_ALREADY_ADDED);
    songs.push_back(song);
    if (songs.size() == 1) {
        currentSong = songs.begin();
    }
}

void Playlist::removeSong(const Song& song) {
    if (songs.empty()) {
        throw MusicPlayerException(PRINT_NO_SONGS_TO_REMOVE);
    }
    songs.remove(song);
}

void Playlist::moveSong(int currentPositionIndex, int newPositionIndex) {

    std::list<Song>::iterator currentPositionIt = songs.begin();
    std::list<Song>::iterator newPositionIt = songs.begin();
    std::advance(currentPositionIt, currentPositionIndex);
    std::advance(newPositionIt, newPositionIndex + 1);
    songs.splice(newPositionIt, songs, currentPositionIt);
}

Song& Playlist::getCurrentSong() const {

    return *currentSong;
} 

void Playlist::nextSong() {
    currentSong++;
    if (currentSong == songs.end()) {
        currentSong = songs.begin();
    }
}

void Playlist::previousSong() {
    currentSong--;
    if (currentSong == songs.end()) {
        currentSong = std::prev(songs.end(), 1);
    }
}

const std::string Playlist::toString() const {
    std::string songList = PRINT_CURRENT_SONGS;
    std::for_each(songs.begin(), songs.end(), AppendItemToString<Song>(songList));
    if (songs.empty()) {
        songList = PRINT_NO_SONGS_IN_PLAYLIST;
    }
    return songList;
}

int Playlist::getSongCount() {
    return songs.size();
}

Song Playlist::getSongByIndex(int songIndex) {
    if (songIndex >= songs.size() || songIndex < 0) {
        throw MusicPlayerException("Invalid index accessed");
    }
    std::list<Song>::iterator it = songs.begin();
    std::advance(it, songIndex);
    return *it;
}