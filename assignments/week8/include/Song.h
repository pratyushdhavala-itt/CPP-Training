#ifndef SONG_H
#define SONG_H

#include <string>

class Song {

private:

    std::string title;
    std::string artist;
    std::string filePath;


public:

    Song(const std::string& title, const std::string& artist, const std::string& filePath);

    const std::string& getSongTitle() const;
    const std::string& getSongArtist() const;
    const std::string& getFilePath() const;
    void setFilePath(const std::string& filePath);
    std::string toString() const;

    bool operator==(const Song& otherSong) const;
};

#endif