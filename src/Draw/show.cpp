#include <string>
#include <chrono>
#include <filesystem>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Generation/tools.hpp"

bool hasFileChanged(std::string sceneFile) {
    static auto lastWriteTime = std::filesystem::last_write_time(sceneFile);
    auto currentWriteTime = std::filesystem::last_write_time(sceneFile);
    if (currentWriteTime != lastWriteTime) {
        lastWriteTime = currentWriteTime;
        return true;
    }
    return false;
}

void showImage(sf::RenderWindow &window, my_Image &image) {
    sf::Sprite sp;
    sf::Texture txt;

    image.imageMutex.lock();
    txt.loadFromImage(image.image);
    image.imageMutex.unlock();
    sp.setTexture(txt);
    window.clear();
    window.draw(sp);
    window.display();
}

int displayImage(sf::RenderWindow &window, my_Image &image, std::string
    sceneFile) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed
                || event.key.code == sf::Keyboard::Escape) {
                renderAtClosing(window);
                window.close();
            }
            if (event.type == sf::Event::KeyPressed
                && event.key.code == sf::Keyboard::Space) {
                screenshot(window);
            }
        }
        if (hasFileChanged(sceneFile))
            return 1;
        showImage(window, image);
    }
    return 0;
}
