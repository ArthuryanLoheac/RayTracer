#include <dlfcn.h>
#include <dirent.h>

#include <memory>
#include <vector>
#include <chrono>
#include <iostream>
#include <string>
#include <cstdio>

#include "Generation/tools.hpp"
#include "Consts/const.hpp"
#include "Primitive/I_Primitive.hpp"
#include "dlLoader/dlLoader.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Ray Tracer");
    sf::Image image;
    image.create(WIDTH, HEIGHT, sf::Color::Black);

    try {
        std::unique_ptr<RayTracer::I_Primitive> sphere =
            dlLoader<RayTracer::I_Primitive>::getLib(
                "./libs/primitive_sphere.so", "getPrimitive");
        generateImage(window, image, sphere);
        displayImage(window, image);
    } catch (const dlLoader<RayTracer::I_Primitive>::dlError &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
