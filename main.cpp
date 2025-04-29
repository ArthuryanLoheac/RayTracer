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

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

static bool verifyPrimLib(const std::string &path) {
    void *handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << path << "(1): " << dlerror() << std::endl;
        return false;
    }
    void* symbolPtr = dlsym(handle, "getPrimitive");
    if (!symbolPtr) {
        std::cerr << path << "(2): " << dlerror() << std::endl;
        dlclose(handle);
        return false;
    }
    try {
        auto test = reinterpret_cast<std::unique_ptr<RayTracer::I_Primitive> *>
            (symbolPtr);
        (void)test;
    } catch(const std::exception& e) {
        std::cerr << path << ": Bad format for entry point." << std::endl;
        return false;
    }
    dlclose(handle);
    return true;
}

std::unique_ptr<RayTracer::I_Primitive>
    getPrim(const std::string &PrimLibPath) {
    void *handle = dlopen(PrimLibPath.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "Error loading library: " << dlerror() << std::endl;
        exit(84);
    }
    auto createModule = reinterpret_cast
        <std::unique_ptr<RayTracer::I_Primitive> (*)()>
        (dlsym(handle, "getPrimitive"));
    if (!createModule) {
        std::cerr << "Error loading symbol: " << dlerror() << std::endl;
        dlclose(handle);
        exit(84);
    }
    auto module = createModule();
    return module;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Ray Tracer");
    sf::Image image;
    image.create(WIDTH, HEIGHT, sf::Color::Black);

    std::string PrimLibPath = "./libs/primitive_sphere.so";
    printf("Loading Primitive library %s...\n", PrimLibPath.c_str());
    if (!verifyPrimLib(PrimLibPath))
        return 84;

    std::unique_ptr<RayTracer::I_Primitive> sphere = getPrim(PrimLibPath);
    sphere->Init();

    generateImage(window, image, sphere);
    displayImage(window, image);
}
