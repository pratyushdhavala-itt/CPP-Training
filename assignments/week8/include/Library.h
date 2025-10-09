#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <algorithm>
#include "Song.h"
#include "ISongSource.h"
#include "AppendItemToString.h"
#include "constants.h"
#include "MusicPlayerException.h"

template <typename T>
class Library {

private:

    std::vector<T> items;

public:

    Library(std::vector<T> items) : items{items} {
        this->items.reserve(20);
    }

    void addItemToLibrary(const T& item) {
        items.push_back(item);
    }

    const std::string toString() const {
        std::string itemList;
        if (items.empty()) {
            itemList = "\nNo songs in the library ! ! !\n";
        } else {
            itemList = PRINT_SONG_LIST;
            std::for_each(items.begin(), items.end(), AppendItemToString<T>(itemList));
        }
        return itemList;
    }

    const std::vector<T>& getAllItems() const {
        return items;
    }

    const T& getItemByIndex(int index) const {
        try {
            return items.at(index);
        } catch (const std::out_of_range& m) {
            throw MusicPlayerException("Invalid index accessed ! ! !");
        }
    }

    void loadItems(ISongSource& songSource) {

        songSource.loadSongs(items);
    }

    int getItemCount() const {

        return items.size();
    }
};

#endif