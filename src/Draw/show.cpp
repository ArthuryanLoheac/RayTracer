#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Generation/tools.hpp"

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

void displayImage(sf::RenderWindow &window, my_Image &image) {
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
        showImage(window, image);
    }
}
