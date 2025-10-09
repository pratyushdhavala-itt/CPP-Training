#ifndef I_SONG_SOURCE
#define I_SONG_SOURCE

#include <vector>
#include "Song.h"

class ISongSource {

public:

    virtual ~ISongSource() = default;
    virtual void loadSongs(std::vector<Song>& songs) = 0;
};

#endif 