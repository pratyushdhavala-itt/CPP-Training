#ifndef MUSIC_PLAYER_EXCEPTION
#define MUSIC_PLAYER_EXCEPTION

#include <stdexcept>

class MusicPlayerException : public std::runtime_error {

public:

    MusicPlayerException(const std::string& message) : std::runtime_error(message) {}
};

#endif