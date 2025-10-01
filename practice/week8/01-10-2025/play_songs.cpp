#include <iostream>
#include <SFML/Audio.hpp>

int main() {
    
    sf::Music music;

    if (!music.openFromFile("song_one.ogg")) {
        std::cout << "cannot open file" << std::endl;
    }

    music.play();

    while (music.getStatus() == sf::SoundSource::Playing) {
        sf::sleep(sf::milliseconds(100));
    }
    
    return 0;
}