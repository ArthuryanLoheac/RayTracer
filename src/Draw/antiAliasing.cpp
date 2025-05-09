#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

void averageAllImages(float i, float j, sf::Image &image,
std::vector<sf::Image> &images) {
    float r = 0;
    float g = 0;
    float b = 0;
    float a = 0;

    for (sf::Image &im : images) {
        r += im.getPixel(i, j).r;
        g += im.getPixel(i, j).g;
        b += im.getPixel(i, j).b;
        a += im.getPixel(i, j).a;
    }
    r /= images.size();
    g /= images.size();
    b /= images.size();
    a /= images.size();
    image.setPixel(i, j, sf::Color(r, g, b, a));
}

void createListImages(std::vector<sf::Image> &images , sf::Image &image) {
    for (int i = 0; i < 9; i++) {
        sf::Image imageTmp;
        imageTmp.create(image.getSize().x, image.getSize().y,
            image.getPixel(0, 0));
        images.push_back(imageTmp);
    }
}
