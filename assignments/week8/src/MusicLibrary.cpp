#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <string>
#include "ISongSource.h"
#include "Song.h"
#include "MusicLibrary.h"
#include "MusicPlayerException.h"
#include "functors.h"

MusicLibrary::MusicLibrary(std::vector<Song> songs) : songs{songs} {
    this->songs.reserve(20);
}

void MusicLibrary::addSongToLibrary(const Song& song) {

    songs.push_back(song);
}

const std::vector<Song> MusicLibrary::getAllSongs() const {

    return songs;
}

const std::string MusicLibrary::showAllSongs() const {
    std::string songList = "\nList of songs in the library:-";
    std::for_each(songs.begin(), songs.end(), AppendSongToString(songList));
    return songList;
}

const Song& MusicLibrary::getSongByIndex(int index) const {

    return songs[index];
}

int MusicLibrary::getSongCount() {
    return songs.size();
}

void MusicLibrary::load(ISongSource& songSource) {

    this->songs = songSource.loadSongs();
}
