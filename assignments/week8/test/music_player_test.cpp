#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "MusicPlayer.h"
#include "IAudioPlayer.h"

class MockAudioPlayer : public IAudioPlayer {

public:

    MOCK_METHOD(bool, load, (const std::string& filePath), (override));
    MOCK_METHOD(void, play, (), (override));
    MOCK_METHOD(void, pause, (), (override));
    MOCK_METHOD(void, stop, (), (override));
};

class MusicPlayerTest : public ::testing::Test {

protected:

    MockAudioPlayer mockPlayer;
    MusicPlayer* player;
    Playlist* playlist;

    void SetUp() override {

        Song songOne{"Fix You", "Coldplay", "/path/to/fix-you/"};
        Song songTwo{"Yellow", "Coldplay", "/path/to/yellow/"};

        std::list<Song> songs{songOne, songTwo};
        playlist = new Playlist("coldplay songs", songs);
        player = new MusicPlayer(&mockPlayer);
    }

    void TearDown() override {

        delete playlist;
        delete player;
    }
};

TEST_F(MusicPlayerTest, GivenPlaylist_WhenLoadPlaylistCalled_ThenPlaylistIsLoaded) {
    
    player->loadPlaylist(*playlist);
    
    EXPECT_EQ(player->getLoadedPlaylist(), playlist);
}

TEST_F(MusicPlayerTest, GivenLoadedPlaylist_WhenPlayCalled_ThenBackendLoadAndPlayCalled) {
    
    player->loadPlaylist(*playlist);
    
    EXPECT_CALL(mockPlayer, load("/path/to/fix-you/"))
        .WillOnce(testing::Return(true));

    EXPECT_CALL(mockPlayer, play());

    player->play();
    const Song& current = player->getCurrentSong();
    
    EXPECT_EQ(current.getSongTitle(), "Fix You");
}

TEST_F(MusicPlayerTest, GivenPlayingSong_WhenPauseCalled_ThenBackendPauseCalled) {
    
    player->loadPlaylist(*playlist);

    EXPECT_CALL(mockPlayer, load("/path/to/fix-you/"))
        .WillOnce(testing::Return(true));

    EXPECT_CALL(mockPlayer, play());
    EXPECT_CALL(mockPlayer, pause());

    player->play();
    player->pause();
}

TEST_F(MusicPlayerTest, GivenPlayingSong_WhenStopCalled_ThenBackendStopCalled) {
    
    player->loadPlaylist(*playlist);

    EXPECT_CALL(mockPlayer, load("/path/to/fix-you/"))
        .WillOnce(testing::Return(true));

    EXPECT_CALL(mockPlayer, play());
    EXPECT_CALL(mockPlayer, stop());

    player->play();
    player->stop();
}

TEST_F(MusicPlayerTest, GivenPlaylist_WhenNextCalled_ThenNextSongPlayed) {

    player->loadPlaylist(*playlist);

    EXPECT_CALL(mockPlayer, load("/path/to/fix-you/"))
        .WillOnce(testing::Return(true));
    EXPECT_CALL(mockPlayer, play())
        .Times(2);
    EXPECT_CALL(mockPlayer, load("/path/to/yellow/"))
        .WillOnce(testing::Return(true));

    player->play();    
    player->next();   

    EXPECT_EQ(player->getCurrentSong().getSongTitle(), "Yellow");
}

TEST_F(MusicPlayerTest, GivenPlaylist_WhenPreviousCalled_ThenPreviousSongPlayed) {
    
    player->loadPlaylist(*playlist);

    EXPECT_CALL(mockPlayer, load("/path/to/fix-you/"))
        .WillOnce(testing::Return(true));

    EXPECT_CALL(mockPlayer, play())
        .Times(2);

    EXPECT_CALL(mockPlayer, load("/path/to/yellow/"))
        .WillOnce(testing::Return(true));

    player->play();     
    player->previous(); 

    EXPECT_EQ(player->getCurrentSong().getSongTitle(), "Yellow");
}