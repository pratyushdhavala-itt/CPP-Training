#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <list>
#include <algorithm>
#include "Playlist.h"
#include "Song.h"
#include "MusicPlayerException.h"
class PlaylistTest : public ::testing::Test {

protected:

    Song songOne{"In My Life", "The Beatles", "/path/to/beatles/"};
    Song songTwo{"Piano Man", "Billy Joel", "/path/to/piano-man/"};
    Song songThree{"Wonderwall", "Oasis", "/path/to/wonderwall/"};

    std::list<Song> testSongs{songOne, songTwo, songThree};
    Playlist playlist{"first-playlist", testSongs};
};

TEST_F(PlaylistTest, GivenPlaylist_WhenConstructed_ThenMembersInitializedCorrectly) {

    EXPECT_EQ(playlist.getPlaylistName(), "first-playlist");
    EXPECT_EQ(playlist.getSongCount(), 3);
}

TEST_F(PlaylistTest, GivenPlaylist_WhenGetAllSongsCalled_ThenCorrectListOfSongsReturned) {

    EXPECT_EQ(playlist.getAllSongs(), testSongs);
}

TEST_F(PlaylistTest, GivenPlaylist_WhenGetAllSongsCalled_ThenSongsNotManipulated) {

    Song songOne{"In My Life", "The Beatles", "/path/to/beatles/"};
    Song songTwo{"Piano Man", "Billy Joel", "/path/to/piano-man/"};
    Song songThree{"Wonderwall", "Oasis", "/path/to/wonderwall/"};
    auto it = playlist.getAllSongs().begin();
    ASSERT_EQ(*it, songOne);
    it++;
    ASSERT_EQ(*it, songTwo);
    it++;
    ASSERT_EQ(*it, songThree);

}

TEST_F(PlaylistTest, GivenPlaylist_WhenNewSongAdded_ThenSongCountIncreases) {

    Song testSong{"Let It Happen", "Tame Impala", "/path/to/let-it-happen/"};

    playlist.addSong(testSong);

    EXPECT_EQ(playlist.getSongCount(), 4);
}

TEST_F(PlaylistTest, GivenPlaylist_WhenNewSongAdded_ThenNewSongIsLastNode) {

    Song testSong{"Let It Happen", "Tame Impala", "/path/to/let-it-happen/"};

    playlist.addSong(testSong);

    EXPECT_EQ(playlist.getAllSongs().back(), testSong);
}

TEST_F(PlaylistTest, GivenPlaylist_WhenSongRemoved_ThenSongCountDecreases) {

    playlist.removeSong(songThree);

    EXPECT_EQ(playlist.getSongCount(), 2);
}

TEST_F(PlaylistTest, GivenPlaylist_WhenSongRemoved_ThenFindSongReturnsEndIterator) {

    playlist.removeSong(songThree);
    std::list<Song> songList = playlist.getAllSongs();
    auto it = std::find(songList.begin(), songList.end(), songThree);

    EXPECT_EQ(it, songList.end());
}

TEST_F(PlaylistTest, GivenEmptyPlaylist_WhenCalledRemoveSong_ThenThrowException) {
    std::list<Song> temp;
    Playlist emptyPlaylist("empty-playlist", temp);

    EXPECT_THROW(emptyPlaylist.removeSong(songOne), MusicPlayerException);
}

TEST_F(PlaylistTest, GivenPlaylist_WhenNextSongCalled_ThenListIteratorMovesForward) {

    Song& previousSong = playlist.getCurrentSong();
    playlist.nextSong();
    Song& nextSong = playlist.getCurrentSong();

    EXPECT_NE(&previousSong, &nextSong);
    EXPECT_EQ(nextSong.getSongTitle(), "Piano Man");
}

TEST_F(PlaylistTest, GivenPlaylist_WhenCalledNextSongOnLastSong_ThenReturnFirstSong) {

    playlist.nextSong();
    playlist.nextSong();
    playlist.nextSong();
    EXPECT_EQ(playlist.getCurrentSong().getSongTitle(), "In My Life");
}

TEST_F(PlaylistTest, GivenPlaylist_WhenCalledPreviousSongOnFirstSong_ThenReturnLastSong) {

    playlist.previousSong();
    EXPECT_EQ(playlist.getCurrentSong().getSongTitle(), "Wonderwall");
}

TEST_F(PlaylistTest, GivenPlaylist_WhenMoveSongCalled_ThenMoveSongToNewPosition) {

    playlist.moveSong(0, 2);
    std::list<Song> songsCopy = playlist.getAllSongs();
    std::list<Song>::iterator it = songsCopy.begin();
    std::advance(it, 2);
    EXPECT_EQ(it->getSongTitle(), "In My Life");
    EXPECT_EQ(songsCopy.begin()->getSongTitle(), "Piano Man");
}

TEST_F(PlaylistTest, GivenPlaylist_WhenGetSongByIndexCalled_ThenReturnCorrectSong) {
    
    Song testSong{"Let Down", "Radiohead", "/path/to/let-down/"};
    playlist.addSong(testSong);
    Song result = playlist.getSongByIndex(3);
    EXPECT_EQ(result, testSong);
}

TEST_F(PlaylistTest, GivenPlaylist_WhenShowAllSongsCalled_ReturnNonEmptyStrign) {

    std::string list = playlist.toString();

    EXPECT_THAT(list, testing::AllOf(
        testing::HasSubstr("Piano Man"),
        testing::HasSubstr("Wonderwall"),
        testing::HasSubstr("In My Life")
    ));
}

TEST_F(PlaylistTest, GivenEmptyPlaylist_WhenShowAllSongsCalled_ReturnNoSongs) {
    std::list<Song> temp;
    Playlist emptyPlaylist("empty-playlist", temp);
    std::string result = emptyPlaylist.toString();
    EXPECT_NE(result.find("No songs in the playlist"), std::string::npos);
}

TEST_F(PlaylistTest, GivenPlaylist_WhenInvalidIndexAccessed_ThenThrowException) {

    EXPECT_THROW(playlist.getSongByIndex(3), MusicPlayerException);
    EXPECT_THROW(playlist.getSongByIndex(-1), MusicPlayerException);
}