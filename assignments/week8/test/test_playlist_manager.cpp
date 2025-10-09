#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PlaylistManager.h"
#include "MusicPlayerException.h"

class PlaylistManagerTest : public ::testing::Test {

protected:

    PlaylistManager* manager;

public:

    void SetUp() override {

        Song songOne{"Thunderstruck", "AC/DC", "/rock/thunderstruck.mp3"};
        Song songTwo{"Highway to Hell", "AC/DC", "/rock/highway.mp3"};
        Song songThree{"Hells Bells", "AC/DC", "/rock/hells.mp3"};

        std::list<Song> testRockSongs{songOne, songTwo, songThree};

        Playlist testRockPlaylist{"Rock Classics", testRockSongs};

        std::map<std::string, Playlist> testPlaylists{{"Rock Classics", testRockPlaylist}};

        manager = new PlaylistManager(testPlaylists);
    }

    void TearDown() override {

        delete manager;
    }
};

TEST_F(PlaylistManagerTest, GivenPlaylists_WhenPlaylistManagerConstructed_ThenPlaylistStoredCorrectly) {
    
    EXPECT_EQ(manager->getPlaylistCount(), 1);
}

TEST_F(PlaylistManagerTest, GivenPlaylistName_WhenCreatePlaylistCalled_ThenPlaylistAdded) {
    
    manager->createPlaylist("Study");

    EXPECT_EQ(manager->getPlaylistCount(), 2);

    Playlist* newPlaylist = manager->getPlaylist("Study");

    EXPECT_EQ(newPlaylist->getPlaylistName(), "Study");
}

TEST_F(PlaylistManagerTest, GivenExistingName_WhenCreatePlaylistCalled_ThenThrowsException) {
    
    EXPECT_THROW(manager->createPlaylist("Rock Classics"), MusicPlayerException);
}

TEST_F(PlaylistManagerTest, GivenPlaylist_WhenAddPlaylistCalled_ThenAddedToMap) {
    std::list<Song> gymSongs{{"Goosebumps", "Travis Scott", "/path/to/goosebumps/"}};
    Playlist gym("Gym Playlist", gymSongs);

    manager->addPlaylist(gym);

    EXPECT_EQ(manager->getPlaylistCount(), 2);
    EXPECT_EQ(manager->getPlaylist("Gym Playlist")->getPlaylistName(), "Gym Playlist");
}

TEST_F(PlaylistManagerTest, GivenExistingPlaylist_WhenDeletePlaylistCalled_ThenRemoved) {
    
    manager->deletePlaylist("Rock Classics");

    EXPECT_EQ(manager->getPlaylistCount(), 0);
}

TEST_F(PlaylistManagerTest, GivenNonExistentPlaylist_WhenDeleteCalled_ThenThrowsException) {
    
    EXPECT_THROW(manager->deletePlaylist("Test"), MusicPlayerException);
}

TEST_F(PlaylistManagerTest, GivenExistingPlaylist_WhenGetPlaylistCalled_ThenReturnCorrectPlaylist) {
    
    Playlist* result = manager->getPlaylist("Rock Classics");

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getPlaylistName(), "Rock Classics");
}

TEST_F(PlaylistManagerTest, GivenInvalidPlaylistName_WhenGetPlaylistCalled_ThenThrowsException) {
    
    EXPECT_THROW(manager->getPlaylist("Test"), MusicPlayerException);
}

TEST_F(PlaylistManagerTest, GivenPlaylistManager_WhenShowAllPlaylistsCalled_ThenReturnsStringWithNames) {
    
    std::string result = manager->toString();
    
    EXPECT_THAT(result, testing::AllOf(
        testing::HasSubstr("Rock Classics")
    ));
}

TEST_F(PlaylistManagerTest, GivenNoPlaylists_WhenShowAllPlaylistsCalled_ThenReturnsEmptyMessage) {
    
    PlaylistManager emptyManager({});
    std::string result = emptyManager.toString();
    
    EXPECT_THAT(result, testing::AllOf(
        testing::HasSubstr("No playlists")
    ));
}