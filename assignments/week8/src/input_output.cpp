#include <iostream>
#include <string>
#include <thread>
#include "input_output.h"
#include "Library.h"
#include "Playlist.h"
#include "PlaylistManager.h"
#include "MusicPlayer.h"
#include "MusicPlayerException.h"
#include "constants.h"

void createPlaylist(std::string& playlistName, PlaylistManager& playlistManager) {
    inputPlaylist(playlistName);
    try {
        playlistManager.createPlaylist(playlistName);
        std::cout << PRINT_PLAYLIST_CREATED << std::endl;
    } catch (const MusicPlayerException& m) {
        std::cout << m.what() << std::endl;
    }

}

void deletePlaylist(std::string& playlistName, PlaylistManager& playlistManager) {
    if (playlistManager.getPlaylistCount() == 0) {
        std::cout << PRINT_NO_PLAYLISTS_TO_DELETE << std::endl;
        return;
    }
    inputPlaylist(playlistName);
    try {
        playlistManager.deletePlaylist(playlistName);
        std::cout << PRINT_PLAYLIST_DELETED << std::endl;
    } catch (const MusicPlayerException& m) {
        std::cout << m.what() << std::endl;
    }
}

void viewPlaylists(int choice, std::string& playlistName, PlaylistManager& playlistManager) {
    std::cout << playlistManager.showAllPlaylists() << std::endl;
    if (playlistManager.getPlaylistCount() == 0) return;
    std::cout << PRINT_VIEW_PLAYLIST_MENU;
    choice = inputChoice(1, 2);
    if (choice == 1) {
        inputPlaylist(playlistName);
        Playlist* playlist = playlistManager.getPlaylist(playlistName);
        std::cout << playlist->showAllSongs() << std::endl;
    }
}

void startMusicPlayer(int choice, std::string& playlistName, MusicPlayer& musicPlayer, PlaylistManager& playlistManager) {
    if (playlistManager.getPlaylistCount() == 0) {
        std::cout << PRINT_NO_PLAYLISTS_TO_PLAY << std::endl;
        return;
    }
    inputPlaylist(playlistName);
    try {
        Playlist* playlist = playlistManager.getPlaylist(playlistName);
        if (playlist->getSongCount() == 0) {
            std::cout << PRINT_NO_SONGS_TO_PLAY << std::endl;
            return;
        }
        musicPlayer.loadPlaylist(*playlist);
        std::cout << PRINT_PLAYLIST_LOADED << std::endl;
        while (true) {
            std::cout << PRINT_MUSIC_PLAYER_MENU << std::endl;
            choice = inputChoice(1, 5);
            switch(choice) {
                case 1:
                    try {
                        musicPlayer.play();
                        std::cout << PRINT_PLAYING + musicPlayer.getCurrentSong().getSongTitle() + PRINT_BY_ARTIST + musicPlayer.getCurrentSong().getSongArtist(); 
                    } catch (const MusicPlayerException& m) {
                        std::cout << m.what() << std::endl;
                    }
                    break;
                case 2:
                    try {       
                        musicPlayer.pause();
                        std::cout << PRINT_SONG_PAUSED << std::endl;
                    } catch (const MusicPlayerException& m) {
                        std::cout << m.what() << std::endl;
                    }
                    break;
                case 3:
                    musicPlayer.next();
                    std::cout << PRINT_SWITCH_TO_NEXT_SONG << std::endl;
                    std::cout << PRINT_PLAYING + musicPlayer.getCurrentSong().getSongTitle() + PRINT_BY_ARTIST + musicPlayer.getCurrentSong().getSongArtist(); 
                    break;
                case 4:
                    musicPlayer.previous();
                    std::cout << PRINT_SWITCH_TO_PREV_SONG << std::endl;
                    std::cout << PRINT_PLAYING + musicPlayer.getCurrentSong().getSongTitle() + PRINT_BY_ARTIST + musicPlayer.getCurrentSong().getSongArtist(); 
                    break;
                case 5:
                    musicPlayer.stop();
                    std::cout << PRINT_SONG_STOPPED << std::endl;
                    return;
            }
        }
    } catch (const MusicPlayerException& m) {
        std::cout << m.what() << std::endl;
    }
}

void addSongToPlaylist(int choice, Playlist* playlist, Library<Song>& musicLibrary) {
    std::cout << musicLibrary.showAllItems() << std::endl;
    while (true) {
        std::cout << PRINT_ENTER_SONG_INDEX_TO_ADD;
        int songIndex = inputChoice(1, musicLibrary.getItemCount()) - 1;
        Song song = musicLibrary.getItemByIndex(songIndex);
        try {
            playlist->addSong(song);
            std::cout << PRINT_SONG_ADDED;
        } catch (const MusicPlayerException& m) {
            std::cout << m.what() << std::endl;
        }
        std::cout << PRINT_ADD_ANOTHER_SONG << std::endl;
        choice = inputChoice(0, 1);
        if (choice == 0) break;
    }
}

void removeSongFromPlaylist(int choice, Playlist* playlist) {
    std::cout << playlist->showAllSongs() << std::endl;
    while (true) {
        if (playlist->getSongCount() == 0) {
            std::cout << PRINT_NO_SONGS_TO_REMOVE << std::endl;
            break;
        }
        std::cout << PRINT_ENTER_SONG_INDEX_TO_REMOVE;
        int songIndex = inputChoice(1, playlist->getSongCount()) - 1;
        Song song = playlist->getSongByIndex(songIndex);
        playlist->removeSong(song);
        std::cout << PRINT_SONG_REMOVED;
        choice = inputChoice(0, 1);
        if (choice == 0) break;
    }
}

void moveSongInPlaylist(int choice, Playlist* playlist) {
    std::cout << playlist->showAllSongs() << std::endl;
    while (true) {
        if (playlist->getSongCount() == 0) {
            std::cout << PRINT_NO_SONGS_TO_REMOVE << std::endl;
            break;
        }
        std::cout << PRINT_ENTER_SONG_INDEX_TO_MOVE;
        int songIndex = inputChoice(1, playlist->getSongCount()) - 1;
        std::cout << PRINT_ENTER_SONG_NEW_INDEX;
        int songNewIndex = inputChoice(1, playlist->getSongCount()) - 1;
        playlist->moveSong(songIndex, songNewIndex);
        std::cout << PRINT_SONG_MOVED;
        choice = inputChoice(0, 1);
        if (choice == 0) break;
    }
}

void editPlaylist(int choice, std::string& playlistName, Library<Song>& musicLibrary, PlaylistManager& playlistManager) {
    if (playlistManager.getPlaylistCount() == 0) {
        std::cout << PRINT_NO_PLAYLISTS_TO_EDIT << std::endl;
        return;
    }
    inputPlaylist(playlistName);
    try {
        Playlist* playlist = playlistManager.getPlaylist(playlistName);
        std::cout << PRINT_EDIT_PLAYLIST_MENU;
        choice = inputChoice(1, 3);
        switch(choice) {
            case 1: 
                addSongToPlaylist(choice, playlist, musicLibrary);
                break;
            case 2: 
                removeSongFromPlaylist(choice, playlist);
                break;
            case 3:
                moveSongInPlaylist(choice, playlist);
                break;
        }
    } catch (const MusicPlayerException m) {
        std::cout << m.what() << std::endl;
    }
}

const std::string& inputPlaylist(std::string& playlistName) {
    std::cout << PRINT_ENTER_PLAYLIST_NAME;
    std::getline(std::cin, playlistName);
    return playlistName;
}

int inputChoice(int minChoice, int maxChoice) {
    char c[3];
    int choice;
    while (true) {
        std::cin.getline(c, 3);
        if (std::cin.fail()) {
            std::cout << PRINT_INVALID_INPUT << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }
        choice = atoi(c);
        if (choice < minChoice || choice > maxChoice) {
            std::cout << PRINT_INVALID_INPUT << std::endl;
            continue;
        }
        break;
    }
    return choice;
}