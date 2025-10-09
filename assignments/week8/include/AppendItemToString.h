#include <string>
#include "Playlist.h"

template <typename T>
class AppendItemToString {

private:

    int index;
    std::string& output;

public:

    AppendItemToString(std::string& output) : output(output), index{1} {}

    void operator()(const T& item) {
        output += "\n" + std::to_string(index) + ". " + item.toString();  
        index++;
    }
};

template <>
class AppendItemToString<std::pair<const std::string, Playlist>> {

private:

    int index = 1;
    std::string& output;

public:

    AppendItemToString(std::string& output, int start = 1)
        : index(start), output(output) {}

    void operator()(const std::pair<const std::string, Playlist>& p) {
        output += "\n" + std::to_string(index++) + ". " + p.second.getPlaylistName();
    }
};
