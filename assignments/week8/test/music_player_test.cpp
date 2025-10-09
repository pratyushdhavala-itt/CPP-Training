#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "MusicPlayer.h"
#include "IAudioPlayer.h"
#include "MusicPlayerException.h"

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
        player->loadPlaylist(*playlist);
    }

    void TearDown() override {

        delete playlist;
        delete player;
    }
};

TEST_F(MusicPlayerTest, GivenMusicPlayer_WhenLoadPlaylistCalled_ThenPlaylistIsLoaded) {
    
    EXPECT_EQ(player->getLoadedPlaylist(), playlist);
}

TEST_F(MusicPlayerTest, GivenMusicPlayer_WhenLoadPlaylistCalled_ThenPlaylistNotManipulated) {
    Song songOne{"Fix You", "Coldplay", "/path/to/fix-you/"};
    Song songTwo{"Yellow", "Coldplay", "/path/to/yellow/"};
    
    EXPECT_EQ(player->getLoadedPlaylist()->getSongByIndex(0), songOne);
    EXPECT_EQ(player->getLoadedPlaylist()->getSongByIndex(1), songTwo);
}

TEST_F(MusicPlayerTest, GivenMusicPlayer_WhenPlayCalled_ThenBackendLoadAndPlayCalled) {
    
    EXPECT_CALL(mockPlayer, load("/path/to/fix-you/"))
        .WillOnce(testing::Return(true));

    EXPECT_CALL(mockPlayer, play());

    player->play();
}

TEST_F(MusicPlayerTest, GivenMusicPlayerBackendFailed_WhenPlayCalled_ThenThrowException) {
    
    EXPECT_CALL(mockPlayer, load("/path/to/fix-you/"))
        .WillOnce(testing::Return(true));

    EXPECT_CALL(mockPlayer, play())
        .WillOnce(testing::Throw(MusicPlayerException("Backend failure ! ! ! Try again later ! ! !")));

    EXPECT_THROW(player->play(), MusicPlayerException);
}

TEST_F(MusicPlayerTest, GivenMusicPlayer_WhenPlayCalled_ThenCurrentSongIsFirstSong) {
    
    player->play();
    const Song& current = player->getCurrentSong();
    
    EXPECT_EQ(current.getSongTitle(), "Fix You");
}

TEST_F(MusicPlayerTest, GivenMusicPlayer_WhenConstructed_ThenCurrentSongIsNull) {

    EXPECT_EQ(player->getCurrentSong(), nullptr);
}

TEST_F(MusicPlayerTest, GivenMusicPlayer_WhenPlayCalled_ThenCurrentSongIsNotNull) {
    
    player->play();

    EXPECT_NE(player->getCurrentSong(), nullptr);
}


TEST_F(MusicPlayerTest, GivenPlayingSong_WhenPauseCalled_ThenBackendPauseCalled) {
    
    EXPECT_CALL(mockPlayer, pause());

    player->pause();
}

TEST_F(MusicPlayerTest, GivenPlayingSong_WhenStopCalled_ThenBackendStopCalled) {

    EXPECT_CALL(mockPlayer, stop());

    player->stop();
}

TEST_F(MusicPlayerTest, GivenNoSongPlayingSong_WhenPauseCalled_ThenThrowException) {

    EXPECT_CALL(mockPlayer, pause())
        .WillOnce(testing::Throw(MusicPlayerException("No song playing ! ! !")));

    EXPECT_THROW(player->pause(), MusicPlayerException);
}

TEST_F(MusicPlayerTest, GivenNoSongPlayingSong_WhenStopCalled_ThenThrowException) {

    EXPECT_CALL(mockPlayer, stop())
        .WillOnce(testing::Throw(MusicPlayerException("No song playing ! ! !")));

    EXPECT_THROW(player->stop(), MusicPlayerException);
}

TEST_F(MusicPlayerTest, GivenPlaylist_WhenNextCalled_ThenExpectBackendCalls) {

    EXPECT_CALL(mockPlayer, play())
        .Times(1);
    EXPECT_CALL(mockPlayer, load("/path/to/yellow/"))
        .WillOnce(testing::Return(true));

    player->next();   
}

TEST_F(MusicPlayerTest, GivenPlaylist_WhenNextCalled_ThenCurrentSongChangedToNextSong) {

    player->next();   

    EXPECT_EQ(player->getCurrentSong().getSongTitle(), "Yellow");
}

TEST_F(MusicPlayerTest, GivenPlaylist_WhenPreviousCalled_ThenExpectBackendCalls) {
    
    EXPECT_CALL(mockPlayer, play())
        .Times(1);
    EXPECT_CALL(mockPlayer, load("/path/to/yellow/"))
        .WillOnce(testing::Return(true));

    player->previous(); 
}

TEST_F(MusicPlayerTest, GivenPlaylist_WhenPreviousCalled_ThenCurrentSongChangedToPreviousSong) {
    
    player->previous(); 

    EXPECT_EQ(player->getCurrentSong().getSongTitle(), "Yellow");
}