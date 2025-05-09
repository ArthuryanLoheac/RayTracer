#pragma once
#include <mutex>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class my_Image {
 public:
    my_Image();
    my_Image(float x, float y, sf::Color fill);
    my_Image(const my_Image&) = delete;
    my_Image& operator=(const my_Image&) = delete;
    my_Image(my_Image&&) = default;
    my_Image& operator=(my_Image&&) = default;

    sf::Image image;
    std::mutex imageMutex;
    void setPixel(float x, float y, sf::Color c);
    sf::Color getPixel(float x, float y);
    float getSizeX();
    float getSizeY();
};

