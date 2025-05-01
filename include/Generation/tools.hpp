#pragma once
#include <memory>

#include "Interfaces/Primitive/I_Primitive.hpp"
#include "Consts/const.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void generateImage(sf::RenderWindow &window, sf::Image &image,
    std::unique_ptr<Light> &Light);
void displayImage(sf::RenderWindow &window, sf::Image &image);
void showImage(sf::RenderWindow &window, sf::Image &image);
void computeTreeValues(std::shared_ptr<Prim> head,
    std::shared_ptr<Prim> parent = nullptr);
