#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "MusicLibrary.h"
#include "Song.h"

class MusicLibraryTest : public testing::Test {

protected:
    MusicLibrary* musicLibrary;
    std::vector<Song> songs;

    void SetUp() {

        songs.emplace_back("Let Down", "Radiohead", "/test/file/path");
        musicLibrary = new MusicLibrary(songs);
    }

    void TearDown() {
        delete musicLibrary;
    }
};

TEST_F(MusicLibraryTest, GivenMusicLibrary_WhenShowAllSongsCalled_ReturnListOfAllSongs) {

    std::string songList = musicLibrary->showAllSongs();

    EXPECT_THAT(songList, testing::AllOf(
        testing::HasSubstr("List of songs in the library:-"),
        testing::HasSubstr("Radiohead"),
        testing::HasSubstr("Let Down")
    ));
}

TEST_F(MusicLibraryTest, GivenSong_WhenAddedToLibrary_SongIsAddedToMusicLibrary) {
    
    Song song{"Runaway", "Kanye West", "/path/to/runaway.ogg"};

    musicLibrary->addSongToLibrary(song);

    EXPECT_THAT(musicLibrary->getAllSongs(), testing::Contains(song));
}

TEST_F(MusicLibraryTest, GivenMusicLibrary_WhenGetAllSongsCalled_ReturnVectorWithAllSongs) {

    EXPECT_EQ(musicLibrary->getAllSongs(), songs);
}

TEST_F(MusicLibraryTest, GivenMusicLibrary_WhenGetSongByIndexCalled_ReturnSongByIndex) {

    Song song{"Runaway", "Kanye West", "/path/to/runaway.ogg"};
    musicLibrary->addSongToLibrary(song);
    
    EXPECT_EQ(musicLibrary->getSongByIndex(1), song);
}

TEST_F(MusicLibraryTest, GivenMusicLibrary_WhenLoadFromDirectoryCalled_AllSongsFromDirectoryAreLoaded) {

    
}
