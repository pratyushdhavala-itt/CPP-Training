#include <gtest/gtest.h>
#include "Song.h"

class SongTest : public testing::Test {

protected:
    Song song{"Let Down", "Radiohead", "/test/file/path"};
};

TEST_F(SongTest, GivenSong_WhenConstructed_ThenMembersInitialisedCorrectly) {

    EXPECT_EQ(song.getSongTitle(), "Let Down");
    EXPECT_EQ(song.getSongArtist(), "Radiohead");
    EXPECT_EQ(song.getFilePath(), "/test/file/path");
}

TEST_F(SongTest, GivenSong_WhenSetSongFilePathCalled_ThenGetSongFilePathReturnsCorrectFilePath) {

    song.setFilePath("updated/file/path");

    EXPECT_EQ(song.getFilePath(), "updated/file/path");
}

TEST_F(SongTest, GivenTwoSameSongs_WhenEqualToOperatorCalled_ThenReturnedTrue) {

    Song anotherSong{"Let Down", "Radiohead", "/test/file/path"};

    EXPECT_TRUE(song == anotherSong);
}

TEST_F(SongTest, GivenTwoDifferentSongs_WhenEqualToOperatorCalled_ThenReturnedFalse) {

    Song anotherSong{"No Surprises", "Radiohead", "/test/file/path"};

    EXPECT_FALSE(song == anotherSong);
}

TEST_F(SongTest, GivenSong_WhenGetSongTitleCalled_ThenReturnSongTitle) {

    EXPECT_EQ(song.getSongTitle(), "Let Down");
}

TEST_F(SongTest, GivenSong_WhenGetSongArtistCalled_ThenReturnSongArtist) {

    EXPECT_EQ(song.getSongArtist(), "Radiohead");
}
