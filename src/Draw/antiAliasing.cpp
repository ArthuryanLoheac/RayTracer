#include <vector>
#include <memory>
#include <utility>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Draw/my_Image.hpp"

void averageAllImages(float i, float j, my_Image &image,
std::vector<std::unique_ptr<my_Image>> &images) {
    float r = 0;
    float g = 0;
    float b = 0;
    float a = 0;

    for (const auto &im : images) {
        r += im->getPixel(i, j).r;
        g += im->getPixel(i, j).g;
        b += im->getPixel(i, j).b;
        a += im->getPixel(i, j).a;
    }
    r /= images.size();
    g /= images.size();
    b /= images.size();
    a /= images.size();
    image.setPixel(i, j, sf::Color(r, g, b, a));
}

void createListImages(std::vector<std::unique_ptr<my_Image>> &images,
    my_Image &image) {
    for (int i = 0; i < 9; i++) {
        auto imageTmp = std::make_unique<my_Image>(image.getSizeX(),
            image.getSizeY(), image.getPixel(0, 0));
        images.push_back(std::move(imageTmp));
    }
}
