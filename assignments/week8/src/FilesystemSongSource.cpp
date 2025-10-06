#include <vector>
#include <filesystem>
#include "MusicPlayerException.h"
#include "Song.h"
#include "FilesystemSongSource.h"

FilesystemSongSource::FilesystemSongSource(std::string directoryName) : directoryName{directoryName} {}

std::vector<Song> FilesystemSongSource::loadSongs() {

    std::vector<Song> songs;

    try {
        if (!std::filesystem::exists(directoryName)) {
            throw MusicPlayerException("Music directory not found ! ! !");
        }
        std::filesystem::directory_iterator it(directoryName);
        std::filesystem::directory_iterator end;
        for (it; it != end; it++) {
            std::filesystem::directory_entry fileEntry = *it;

            if (fileEntry.is_regular_file()) {
                std::string filename = fileEntry.path().stem();
                int separatorPosition = filename.find(" - ");
                
                if (separatorPosition != std::string::npos) {
                    std::string filePath = fileEntry.path();
                    std::string artist = filename.substr(0, separatorPosition);
                    std::string title = filename.substr(separatorPosition + 3);
                    songs.emplace_back(title, artist, filePath);
                }
            }
        }
        return songs;
    } catch (const std::filesystem::filesystem_error& e) {
        throw MusicPlayerException("Error accessing directory: " + std::string(e.what()));
    }
}
