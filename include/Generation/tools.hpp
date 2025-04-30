#pragma once
#include <memory>

#include "Interfaces/Primitive/I_Primitive.hpp"
#include "Consts/const.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void generateImage(sf::RenderWindow &window, sf::Image &image,
    std::unique_ptr<Prim> &s, std::unique_ptr<Light> &Light);
void displayImage(sf::RenderWindow &window, sf::Image &image);
