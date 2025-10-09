#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <vector>
#include "Library.h"
#include "ISongSource.h"
#include "Song.h"

class MockSongSource : public ISongSource {

public:

    MOCK_METHOD(void, loadSongs, (std::vector<Song>&), (override));

};

class MusicLibraryTest : public ::testing::Test {

protected:

    Library<Song>* library;
    MockSongSource mockSource;
    std::vector<Song> testSongs;

    void SetUp() override {
        Song songOne{"Believer", "Imagine Dragons", "/path/to/believer/"};
        Song songTwo{"Radioactive", "Imagine Dragons", "/path/to/radioactive/"};
        testSongs.assign({songOne, songTwo});

        library = new Library<Song>(testSongs);
    }

    void TearDown() override {

        delete library;
    }
};

TEST_F(MusicLibraryTest, GivenInitialSongs_WhenConstructed_ThenSongsStoredCorrectly) {

    EXPECT_EQ(library->getItemCount(), 2);
    EXPECT_EQ(library->getAllItems().at(0).getSongTitle(), "Believer");
    EXPECT_EQ(library->getAllItems().at(1).getSongTitle(), "Radioactive");
}

TEST_F(MusicLibraryTest, GivenLibrary_WhenGetSongByIndexCalled_ThenReturnCorrectSong) {
    
    const Song& testSong = library->getItemByIndex(1);
    
    EXPECT_EQ(testSong.getSongTitle(), "Radioactive");
}

TEST_F(MusicLibraryTest, GivenLibrary_WhenNewSongAdded_ThenSongCountIncreases) {
    
    Song newSong{"Demons", "Imagine Dragons", "/path/to/demons/"};
    library->addItemToLibrary(newSong);
    
    EXPECT_EQ(library->getItemCount(), 3);
    EXPECT_EQ(library->getAllItems().back().getSongTitle(), "Demons");
}

TEST_F(MusicLibraryTest, GivenLibrary_WhenShowAllSongsCalled_ThenReturnsStringWithSongs) {
    
    std::string list = library->toString();

    EXPECT_THAT(list, testing::AllOf(
        testing::HasSubstr("Imagine"),
        testing::HasSubstr("Radioactive")
    ));
}

TEST_F(MusicLibraryTest, GivenMockSongSource_WhenLoadCalled_ThenLibraryLoadsMockedSongs) {

    EXPECT_CALL(mockSource, loadSongs(testSongs))
        .Times(1);

    library->loadItems(mockSource);

    EXPECT_EQ(library->getItemCount(), 2);
    EXPECT_EQ(library->getItemByIndex(0).getSongTitle(), "Believer");
    EXPECT_EQ(library->getItemByIndex(1).getSongTitle(), "Radioactive");
}

TEST_F(MusicLibraryTest, GivenLibrary_WhenInvalidIndexAccessed_ThenThrowException) {

   EXPECT_THROW(library->getItemByIndex(10), MusicPlayerException);
}

TEST_F(MusicLibraryTest, GivenLibrary_WhenGetAllSongsCalled_ThenReturnSameContainer) {

    EXPECT_EQ(testSongs, library->getAllItems());
}

TEST_F(MusicLibraryTest, GivenLibrary_WhenGetAllSongsCalled_ThenContainerNotManipulated) {
    Song songOne{"Believer", "Imagine Dragons", "/path/to/believer/"};
    Song songTwo{"Radioactive", "Imagine Dragons", "/path/to/radioactive/"};
    EXPECT_EQ(library->getAllItems()[0], songOne);
    EXPECT_EQ(library->getAllItems()[1], songTwo);
}

TEST_F(MusicLibraryTest, GivenEmptyLibrary_WhenToStringCalled_ThenReturnNoSongMessage) {
    std::vector<Song> emptyList;
    Library<Song> emptyLibrary(emptyList);
    std::string expected = "\nNo songs in the library ! ! !\n";
    EXPECT_EQ(emptyLibrary.toString(), expected);
}
