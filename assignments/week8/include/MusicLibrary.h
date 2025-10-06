#ifndef MUSIC_LIBRARY_H
#define MUSIC_LIBRARY_H

#include <vector>
#include "Song.h"
#include "ISongSource.h"
class MusicLibrary {

private:

    std::vector<Song> songs;

public:

    MusicLibrary(std::vector<Song> songs);

    void addSongToLibrary(const Song& song);
    const std::string showAllSongs() const;
    const std::vector<Song> getAllSongs() const;
    const Song& getSongByIndex(int index) const;
    void load(ISongSource& songSource);
    int getSongCount();
};

#endif