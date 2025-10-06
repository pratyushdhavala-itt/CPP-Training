#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <string>
#include "Library.h"
#include "Playlist.h"
#include "PlaylistManager.h"
#include "MusicPlayer.h"

int inputChoice(int minChoice, int maxChoice);
const std::string& inputPlaylist(std::string& playlistName);
void editPlaylist(int choice, std::string& playlistName, Library<Song>& musicLibrary, PlaylistManager& playlistManager);
void startMusicPlayer(int choice, std::string& playlistName, MusicPlayer& musicPlayer, PlaylistManager& playlistManager);
void viewPlaylists(int choice, std::string& playlistName, PlaylistManager& playlistManager);
void createPlaylist(std::string& playlistName, PlaylistManager& playlistManager);
void addSongToPlaylist(int choice, Playlist* playlist, Library<Song>& musicLibrary);
void removeSongFromPlaylist(int choice, Playlist* playlist);
void moveSongInPlaylist(int choice, Playlist* playlist);
void deletePlaylist(std::string& playlistName, PlaylistManager& playlistManager);

#endif