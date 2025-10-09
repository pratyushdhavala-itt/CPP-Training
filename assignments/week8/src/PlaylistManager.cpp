#include <string>
#include <map>
#include <algorithm>
#include "PlaylistManager.h"
#include "Playlist.h"
#include "MusicPlayerException.h"
#include "AppendItemToString.h"
#include "constants.h"

PlaylistManager::PlaylistManager(const std::map<std::string, Playlist>& playlists) 
    : playlists{playlists} {
}

Playlist* PlaylistManager::getPlaylist(const std::string& playlistName) {
    std::map<std::string, Playlist>::iterator it = playlists.find(playlistName);
    if (it == playlists.end()) {
        throw MusicPlayerException(PRINT_PLAYLIST_DOES_NOT_EXIST);

    }
    return &it->second;
}

int PlaylistManager::getPlaylistCount() const {
    return playlists.size();
}

void PlaylistManager::createPlaylist(const std::string& playlistName) {
    if (playlists.find(playlistName) != playlists.end()) {
        throw MusicPlayerException(PRINT_PLAYLIST_ALREADY_EXISTS);
    }
    std::list<Song> songs;
    Playlist playlist(playlistName, songs);
    addPlaylist(playlist);
}

void PlaylistManager::addPlaylist(const Playlist& playlist) {

    playlists.emplace(playlist.getPlaylistName(), playlist);
}

void PlaylistManager::deletePlaylist(const std::string& playlistName) {
    if (playlists.find(playlistName) == playlists.end()) {
        throw MusicPlayerException(PRINT_PLAYLIST_DOES_NOT_EXIST);
    }
    playlists.erase(playlistName);
}

std::string PlaylistManager::toString() const {
    int index = 1;
    std::string allPlaylists = PRINT_PLAYLISTS;
    std::for_each(playlists.begin(), playlists.end(), 
        AppendItemToString<std::pair<const std::string, Playlist>>(allPlaylists));

    if (playlists.empty()) {
        allPlaylists = PRINT_NO_PLAYLISTS;
    }
    return allPlaylists;
}
