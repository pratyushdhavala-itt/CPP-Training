#include <string>
#include <list>
#include <algorithm>
#include "Playlist.h"
#include "Song.h"
#include "MusicPlayerException.h"
#include "functors.h"

Playlist::Playlist(const std::string& playlistName, std::list<Song> songs) 
    : playlistName{playlistName}, songs{songs} {
}

const std::string& Playlist::getPlaylistName() const {

    return playlistName;
}

std::list<Song> Playlist::getAllSongs() const {

    return songs;
}

void Playlist::addSong(const Song& song) {
    songs.push_back(song);
    if (songs.size() == 1) {
        currentSong = songs.begin();
    }
}

void Playlist::removeSong(const Song& song) {
    if (songs.empty()) {
        throw MusicPlayerException("No songs to remove ! ! !");
    }
    songs.remove(song);
}

void Playlist::moveSong(int currentPositionIndex, int newPositionIndex) {

    std::list<Song>::iterator currentPositionIt = songs.begin();
    std::list<Song>::iterator newPositionIt = songs.begin();
    std::advance(currentPositionIt, currentPositionIndex);
    std::advance(newPositionIt, newPositionIndex);
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

const std::string Playlist::showAllSongs() const {
    std::string songList = "\nCurrent songs in your playlist:-";
    std::for_each(songs.begin(), songs.end(), AppendSongToString(songList));
    if (songs.empty()) {
        songList = "\nNo songs in the playlist ! ! !";
    }
    return songList;
}

int Playlist::getSongCount() {
    return songs.size();
}

Song Playlist::getSongByIndex(int songIndex) {

    std::list<Song>::iterator it = songs.begin();
    std::advance(it, songIndex);
    return *it;
}