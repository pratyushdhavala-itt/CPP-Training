#include <string>
#include "Song.h"

Song::Song(const std::string& title, const std::string& artist, const std::string& filePath) 
    : title{title}, artist{artist}, filePath{filePath} {}


const std::string& Song::getSongTitle() const {

    return title;
}

const std::string& Song::getSongArtist() const {

    return artist;
}

const std::string& Song::getFilePath() const {

    return filePath;
}

void Song::setFilePath(const std::string& filePath) {

    this->filePath = filePath;
}

bool Song::operator==(const Song& otherSong) const {

    return (title == otherSong.title) && 
           (artist == otherSong.artist) &&
           (filePath == otherSong.filePath);
}