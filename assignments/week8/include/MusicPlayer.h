#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include <SFML/Audio.hpp>
#include "Playlist.h"
#include "IAudioBackend.h"

class MusicPlayer {

private:

    IAudioBackend* backendPlayer;
    Playlist* currentPlaylist;
    Song* currentSong;

public:

    MusicPlayer(IAudioBackend* backendPlayer);

    void loadPlaylist(Playlist& playlist);
    void play();
    void pause();
    void stop();
    void next();
    void previous();
    const Song& getCurrentSong();
};

#endif