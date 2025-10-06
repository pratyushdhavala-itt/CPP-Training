#ifndef FILE_SYSTEM_SONG_SOURCE_H
#define FILE_SYSTEM_SONG_SOURCE_H

#include <string>
#include <vector>
#include "Song.h"
#include "ISongSource.h"

class FilesystemSongSource : public ISongSource {

private:
    
    std::string directoryName;

public:

    FilesystemSongSource(std::string directoryName);

    std::vector<Song> loadSongs() override;
};

#endif