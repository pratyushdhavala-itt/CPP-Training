#ifndef CONSTANTS_H
#define CONSTANTS_H

inline const char* PRINT_MAIN_MENU = "\nWelcome to the Music Player ! ! !\nPlease choose your choice from the below options:-\n   1. View all songs in the Music Library\n   2. View your playlists\n   3. Create playlist\n   4. Edit playlist\n   5. Delete playlist\n   6. Play songs from a playlist\nEnter your option: ";
inline const char* MUSIC_DIRECTORY = "./tracks/";
inline const char* PRINT_PLAYLIST_CREATED = "\nPlaylist created successfully ! ! !";
inline const char* PRINT_PLAYLIST_DELETED = "\nPlaylist deleted successfully ! ! !";
inline const char* PRINT_PLAYLIST_LOADED = "\nPlaylist loaded successfully";
inline const char* PRINT_VIEW_PLAYLIST_MENU = "\nPlease select from the below options:-\n   1. View all songs in a playlist\n   2. Go back to main menu\nEnter your option: ";
inline const char* PRINT_MUSIC_PLAYER_MENU = "\n---------- Music Player Menu ----------\nPlease select from the below options:-\n   1. Play\n   2. Pause\n   3. Next\n   4. Previous\n   5. Exit Music Player\nEnter your option: ";
inline const char* PRINT_EDIT_PLAYLIST_MENU = "\nPlease choose your choice from the below options:-\n   1. Add a song from the music library   2. Remove a song from the playlist   3. Change a song's position\nEnter your option: ";
inline const char* PRINT_ENTER_SONG_INDEX_TO_ADD = "\nPlease enter the song's serial number to be added: ";
inline const char* PRINT_SONG_ADDED = "\nSong successfully added ! ! !\nEnter (1) if you want to add another song. Enter (0) to go back to main menu\nEnter your choice: ";
inline const char* PRINT_ENTER_SONG_INDEX_TO_REMOVE = "\nPlease enter the song's serial number to be removed: ";
inline const char* PRINT_SONG_REMOVED = "\nSong successfully removed ! ! !\nEnter (1) if you want to remove another song. Enter (0) to go back to main menu\nEnter your choice: ";
inline const char* PRINT_ENTER_PLAYLIST_NAME = "\nEnter your playlist's name: ";
inline const char* PRINT_INVALID_INPUT = "\nInvalid input ! ! ! Try again ! ! !";
inline const char* PRINT_ENTER_SONG_INDEX_TO_MOVE = "\nPlease enter the song's serial number to be moved: ";
inline const char* PRINT_ENTER_SONG_NEW_INDEX = "\nPlease enter the new position of the Song: ";
inline const char* PRINT_SONG_MOVED = "\nSong successfully moved ! ! !\nEnter (1) if you want to move another song. Enter (0) to go back to main menu\nEnter your choice: ";
inline const char* PRINT_NO_PLAYLISTS_TO_DELETE = "\nNo playlists to delete ! ! !";
inline const char* PRINT_NO_PLAYLISTS_TO_PLAY = "\nNo playlists to play ! ! !";
inline const char* PRINT_NO_SONGS_TO_PLAY = "\nNo songs to play in this playlist ! ! !";
inline const char* PRINT_PLAYING = "\nPlaying ";
inline const char* PRINT_SONG_PAUSED = "\nSong paused ! ! !";
inline const char* PRINT_BY_ARTIST = " by ";
inline const char* PRINT_SWITCH_TO_NEXT_SONG = "\nSwitched to next song ! ! !";
inline const char* PRINT_SWITCH_TO_PREV_SONG = "\nSwitched to previous song ! ! !";
inline const char* PRINT_NO_SONGS_TO_REMOVE = "\nNo songs to remove ! ! !";
inline const char* PRINT_NO_PLAYLISTS_TO_EDIT = "\nNo playlists to edit ! ! !";

#endif