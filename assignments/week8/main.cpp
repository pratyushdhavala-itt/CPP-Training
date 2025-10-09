#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "constants.h"
#include "Song.h"
#include "MusicPlayer.h"
#include "Library.h"
#include "PlaylistManager.h"
#include "Playlist.h"
#include "MusicPlayerException.h"
#include "SFMLAudioPlayer.h"
#include "FilesystemSongSource.h"
#include "input_output.h"

int main() {
    SFMLAudioPlayer sfmlPlayer;
    MusicPlayer musicPlayer(&sfmlPlayer);
    std::vector<Song> songs;
    std::map<std::string, Playlist> playlists;
    Library<Song> musicLibrary(songs);
    PlaylistManager playlistManager(playlists);
    FilesystemSongSource songSource(MUSIC_DIRECTORY);
    std::string playlistName;
    try {
        musicLibrary.loadItems(songSource);
    } catch (const MusicPlayerException& m) {
        std::cout << m.what() << std::endl;
        return 0;
    }
    std::cout << PRINT_WELCOME << std::endl;
    while (true) {
        std::cout << PRINT_MAIN_MENU;
        int choice = inputChoice(1, 6);
        switch(choice) {
            case 1: 
                std::cout << musicLibrary.showAllItems() << std::endl;
                break;
            case 2: 
                viewPlaylists(choice, playlistName, playlistManager);
                break;
            case 3: 
                createPlaylist(playlistName, playlistManager);
                break;
            case 4: 
                editPlaylist(choice, playlistName, musicLibrary, playlistManager);
                break;
            case 5: 
                deletePlaylist(playlistName, playlistManager);
                break;
            case 6: 
                startMusicPlayer(choice, playlistName, musicPlayer, playlistManager);
                break;
            default: 
                break;
        }
    }
}
