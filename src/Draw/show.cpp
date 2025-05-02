#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

void showImage(sf::RenderWindow &window, sf::Image &image) {
    sf::Sprite sp;
    sf::Texture txt;

    txt.loadFromImage(image);
    sp.setTexture(txt);
    window.clear();
    window.draw(sp);
    window.display();
}

void displayImage(sf::RenderWindow &window, sf::Image &image) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        showImage(window, image);
    }
}
