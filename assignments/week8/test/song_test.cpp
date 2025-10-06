#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Song.h"

class SongTest : public testing::Test {

public:
    Song song;

    SongTest() : song{"Let Down", "Radiohead", "/test/file/path"} {}
};

TEST_F(SongTest, GivenSong_WhenGetSongTitleCalled_ThenReturnSongTitle) {

    EXPECT_EQ(song.getSongTitle(), "Let Down");
}

TEST_F(SongTest, GivenSong_WhenGetSongArtistCalled_ThenReturnSongArtist) {

    EXPECT_EQ(song.getSongArtist(), "Radiohead");
}

TEST_F(SongTest, GivenSong_WhenGetSongFilePathCalled_ThenReturnSongFilePath) {

    EXPECT_EQ(song.getFilePath(), "/test/file/path");
}

TEST_F(SongTest, GivenSong_WhenSetSongFilePathCalled_ThenGetSongFilePathReturnsCorrectFilePath) {

    song.setFilePath("updated/file/path");

    EXPECT_EQ(song.getFilePath(), "updated/file/path");
}