#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <mutex>

class my_Image {
 public:
    my_Image();
    my_Image(float x, float y, sf::Color fill);
    my_Image(const my_Image&) = delete; // Prevent copying
    my_Image& operator=(const my_Image&) = delete; // Prevent copy assignment
    my_Image(my_Image&&) = default; // Allow moving
    my_Image& operator=(my_Image&&) = default; // Allow move assignment

    sf::Image image;
    std::mutex imageMutex;
    void setPixel(float x, float y, sf::Color c);
    sf::Color getPixel(float x, float y);
    float getSizeX();
    float getSizeY();
};

