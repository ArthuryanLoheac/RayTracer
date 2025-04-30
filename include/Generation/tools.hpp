#pragma once
#include <memory>

#include "Interfaces/Primitive/I_Primitive.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void generateImage(sf::RenderWindow &window, sf::Image &image,
    std::unique_ptr<RayTracer::I_Primitive> &s);
void displayImage(sf::RenderWindow &window, sf::Image &image);
