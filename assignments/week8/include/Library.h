#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <algorithm>
#include "Song.h"
#include "ISongSource.h"
#include "AppendItemToString.h"
#include "constants.h"

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

    const std::string showAllItems() const {

        std::string itemList = PRINT_SONG_LIST;
        std::for_each(items.begin(), items.end(), AppendItemToString<T>(itemList));
        return itemList;
    }

    const std::vector<T>& getAllItems() const {

        return items;
    }

    const T& getItemByIndex(int index) const {

        return items[index];
    }

    void loadItems(ISongSource& songSource) {

        songSource.loadSongs(items);
    }

    int getItemCount() const {

        return items.size();
    }
};

#endif