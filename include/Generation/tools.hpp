#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Interfaces/Primitive/I_Primitive.hpp"
#include "Consts/const.hpp"
#include "Draw/my_Image.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

// Create Image
int generateImage(sf::RenderWindow &window, my_Image &image, std::string
    sceneFile);

// Render image
int displayImage(sf::RenderWindow &window, my_Image &image, std::string
    sceneFile);
void showImage(sf::RenderWindow &window, my_Image &image);

// Compute values of the tree
void computeTreeValues(std::shared_ptr<Prim> head,
    std::shared_ptr<Prim> parent = nullptr);

// Create Image
void screenshot(sf::RenderWindow &window);
void renderAtClosing(sf::RenderWindow &window);
std::string getTimestampAsString();
// ----> Antialiasing
void createListImages(std::vector<std::unique_ptr<my_Image>> &images,
    my_Image &image);
void averageAllImages(float i, float j, my_Image &image,
    std::vector<std::unique_ptr<my_Image>> &images);

// Random tools
bool hasFileChanged(std::string sceneFile);
