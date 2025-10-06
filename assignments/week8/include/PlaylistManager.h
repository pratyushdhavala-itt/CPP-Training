#ifndef PLAYLIST_MANAGER_H
#define PLAYLIST_MANAGER_H

#include <map>
#include <string>
#include "Playlist.h"

class PlaylistManager {

private:

    std::map<std::string, Playlist> playlists;

public:

    PlaylistManager(const std::map<std::string, Playlist>& playlists);

    Playlist* getPlaylist(const std::string& playlistName);
    void createPlaylist(const std::string& playlistName);
    void addPlaylist(const Playlist& playlist);
    void deletePlaylist(const std::string& playlistName);
    std::string showAllPlaylists() const;
    int getPlaylistCount() const;
};

#endif