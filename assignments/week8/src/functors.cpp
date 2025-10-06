#include "functors.h"

AppendSongToString::AppendSongToString(std::string& output) : output{output}, index{1} {}

void AppendSongToString::operator() (const Song& song) {
    output += "\n" + std::to_string(index) + ". " + song.getSongArtist() + " - " + song.getSongTitle();
    index++;
}

AppendPlaylistToString::AppendPlaylistToString(std::string& output) : output{output}, index{1} {}

void AppendPlaylistToString::operator() (const std::pair<std::string, Playlist>& pair) {

    output += "\n" + std::to_string(index) + ". " + pair.second.getPlaylistName();
    index++;
}