#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <filesystem>
#include <fstream>
#include "FilesystemSongSource.h"
#include "MusicPlayerException.h"

class FilesystemSongSourceTest : public testing::Test {

protected:

    std::string testDirectory = "test_directory";

    void SetUp() override {

        std::filesystem::create_directory(testDirectory);

        std::ofstream(testDirectory + "/Imagine Dragons - Believer.mp3").put(' ');
        std::ofstream(testDirectory + "/Coldplay - Yellow.mp3").put(' ');
        std::ofstream(testDirectory + "/InvalidFileName.mp3").put(' ');
    } 

    void TearDown() override {

        std::filesystem::remove_all(testDirectory);
    }
};

TEST_F(FilesystemSongSourceTest, GivenDirectory_WhenLoadSongsCalled_ThenSongsParsed) {
    
    FilesystemSongSource source(testDirectory);
    std::vector<Song> songs;
    source.loadSongs(songs);

    EXPECT_EQ(songs.size(), 2);

    EXPECT_EQ(songs[0].getSongArtist(), "Imagine Dragons");
    EXPECT_EQ(songs[0].getSongTitle(), "Believer");

    EXPECT_EQ(songs[1].getSongArtist(), "Coldplay");
    EXPECT_EQ(songs[1].getSongTitle(), "Yellow");
}

TEST_F(FilesystemSongSourceTest, GivenInvalidDirectory_WhenLoadSongsCalled_ThenThrowsException) {
    std::vector<Song> songs;

    FilesystemSongSource source("does_not_exist");
    EXPECT_THROW(source.loadSongs(songs), MusicPlayerException);
}

TEST_F(FilesystemSongSourceTest, GivenInvalidFileName_WhenLoadSongsCalled_ThenSkipSong) {
    
    FilesystemSongSource source(testDirectory);
    std::vector<Song> songs;
    source.loadSongs(songs);

    bool hasInvalidFile = false;
    for (const auto& s : songs) {
        if (s.getSongTitle() == "InvalidFileName")
            hasInvalidFile = true;
    }

    EXPECT_FALSE(hasInvalidFile); 
}