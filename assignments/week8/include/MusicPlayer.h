#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include <SFML/Audio.hpp>
#include "Playlist.h"
#include "IAudioPlayer.h"

class MusicPlayer {

private:

    IAudioPlayer* audioPlayer;
    Playlist* currentPlaylist;
    Song* currentSong;

public:

    MusicPlayer(IAudioPlayer* backendPlayer);

    void loadPlaylist(Playlist& playlist);
    void play();
    void pause();
    void stop();
    void next();
    void previous();
    const Song& getCurrentSong();
    Playlist* getLoadedPlaylist() const;
};

#endif