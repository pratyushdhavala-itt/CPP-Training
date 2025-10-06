#ifndef I_SONG_SOURCE
#define I_SONG_SOURCE

#include <vector>
#include "Song.h"

class ISongSource {

public:

    virtual ~ISongSource() = default;
    virtual std::vector<Song> loadSongs() = 0;

};

#endif 