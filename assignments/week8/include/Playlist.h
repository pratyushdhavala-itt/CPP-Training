#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <list>
#include "Song.h"

class Playlist {

private:

    std::string playlistName;
    std::list<Song> songs;
    std::list<Song>::iterator currentSong;

public:

    Playlist(const std::string& playlistName, std::list<Song>& songs);

    const std::list<Song>& getAllSongs() const;
    const std::string& getPlaylistName() const;
    void addSong(const Song& song);
    void removeSong(const Song& song);
    void moveSong(int currentPositionIndex, int newPosition);
    Song& getCurrentSong() const;
    void nextSong();
    void previousSong();
    const std::string toString() const;
    int getSongCount();
    Song getSongByIndex(int songIndex);
};

#endif