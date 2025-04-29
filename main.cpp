#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Generation/tools.hpp"
#include "Consts/const.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Ray Tracer");
    sf::Image image;
    image.create(WIDTH, HEIGHT, sf::Color::Black);

    generateImage(window, image);
    displayImage(window, image);
}
