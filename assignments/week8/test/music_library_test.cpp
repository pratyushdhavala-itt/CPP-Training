#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>
#include "MusicLibrary.h"
#include "ISongSource.h"
#include "Song.h"

class MockSongSource : public ISongSource {

public:

    MOCK_METHOD(std::vector<Song>, loadSongs, (), (override));

};

class MusicLibraryTest : public ::testing::Test {

protected:

    MusicLibrary* library;
    MockSongSource mockSource;

    void SetUp() override {
        Song songOne{"Believer", "Imagine Dragons", "/path/to/believer/"};
        Song songTwo{"Radioactive", "Imagine Dragons", "/path/to/radioactive/"};
        std::vector<Song> testSongs {songOne, songTwo};

        library = new MusicLibrary(testSongs);
    }

    void TearDown() override {

        delete library;
    }
};

TEST_F(MusicLibraryTest, GivenInitialSongs_WhenConstructed_ThenSongsStoredCorrectly) {

    EXPECT_EQ(library->getSongCount(), 2);
    EXPECT_EQ(library->getAllSongs().at(0).getSongTitle(), "Believer");
    EXPECT_EQ(library->getAllSongs().at(1).getSongTitle(), "Radioactive");
}

TEST_F(MusicLibraryTest, GivenLibrary_WhenGetSongByIndexCalled_ThenReturnCorrectSong) {
    
    const Song& testSong = library->getSongByIndex(1);
    
    EXPECT_EQ(testSong.getSongTitle(), "Radioactive");
}

TEST_F(MusicLibraryTest, GivenLibrary_WhenNewSongAdded_ThenSongCountIncreases) {
    
    Song newSong{"Demons", "Imagine Dragons", "/path/to/demons/"};
    library->addSongToLibrary(newSong);
    
    EXPECT_EQ(library->getSongCount(), 3);
    EXPECT_EQ(library->getAllSongs().back().getSongTitle(), "Demons");
}

TEST_F(MusicLibraryTest, GivenLibrary_WhenShowAllSongsCalled_ThenReturnsStringWithSongs) {
    
    std::string list = library->showAllSongs();

    EXPECT_THAT(list, testing::AllOf(
        testing::HasSubstr("Imagine"),
        testing::HasSubstr("Radioactive")
    ));
}

TEST_F(MusicLibraryTest, GivenMockSongSource_WhenLoadCalled_ThenLibraryLoadsMockedSongs) {

    std::vector<Song> mockSongs{
        {"Summer Of '69", "Bryan Adams", "/path/to/summer/"},
        {"It's My Life", "Bon Jovi", "/path/to/jovi/"}
    };

    EXPECT_CALL(mockSource, loadSongs())
        .Times(1)
        .WillOnce(::testing::Return(mockSongs));

    library->load(mockSource);

    EXPECT_EQ(library->getSongCount(), 2);
    EXPECT_EQ(library->getSongByIndex(0).getSongTitle(), "Summer Of '69");
    EXPECT_EQ(library->getSongByIndex(1).getSongTitle(), "It's My Life");
}