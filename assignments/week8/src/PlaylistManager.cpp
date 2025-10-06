#include <string>
#include <map>
#include <algorithm>
#include "PlaylistManager.h"
#include "Playlist.h"
#include "MusicPlayerException.h"
#include "functors.h"

PlaylistManager::PlaylistManager(const std::map<std::string, Playlist>& playlists) 
    : playlists{playlists} {
}

Playlist* PlaylistManager::getPlaylist(const std::string& playlistName) {
    std::map<std::string, Playlist>::iterator it = playlists.find(playlistName);
    if (it == playlists.end()) {
        throw MusicPlayerException("\nPlaylist with this name does not exist ! ! !");

    }
    return &it->second;
}

int PlaylistManager::getPlaylistCount() const {
    return playlists.size();
}


void PlaylistManager::createPlaylist(const std::string& playlistName) {
    if (playlists.find(playlistName) != playlists.end()) {
        throw MusicPlayerException("\nPlaylist with same name already exitst ! ! !");
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
        throw MusicPlayerException("\nPlaylist with this name does not exist ! ! !");
    }
    playlists.erase(playlistName);
}

std::string PlaylistManager::showAllPlaylists() const {
    int index = 1;
    std::string allPlaylists = "\nList of all playlists:-";
    std::for_each(playlists.begin(), playlists.end(), AppendPlaylistToString(allPlaylists));

    if (playlists.empty()) {
        allPlaylists = "\nNo playlists ! ! !";
    }
    return allPlaylists;
}
