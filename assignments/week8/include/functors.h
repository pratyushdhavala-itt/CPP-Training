#ifndef FUNCTORS_H
#define FUNCTORS_H

#include <string>
#include "Playlist.h"
#include "Song.h"

struct AppendSongToString {

    std::string& output;
    int index;

    AppendSongToString(std::string& output);

    void operator() (const Song& song);
};

struct AppendPlaylistToString {

    std::string& output;
    int index;

    AppendPlaylistToString(std::string& output);

    void operator() (const std::pair<std::string, Playlist>& p);
};

#endif