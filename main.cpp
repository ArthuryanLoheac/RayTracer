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
#include "Interfaces/Primitive/I_Primitive.hpp"
#include "Interfaces/Light/I_Light.hpp"
#include "dlLoader/dlLoader.hpp"
#include "Parsing/Parsing.hpp"
#include "Scene/Scene.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

static void setupAndRun(sf::RenderWindow &window, sf::Image &image) {
    RayTracer::Scene::i->ObjectHead = dlLoader<Prim>::getLib(
        "./libs/primitive_none.so", "getPrimitive");
    RayTracer::Scene::i->ObjectHead->AddChildren(dlLoader<Prim>::getLib(
       "./libs/light_ambient.so", "getLight"));

    RayTracer::Scene::i->ObjectHead->AddChildren(
        dlLoader<Prim>::getLib("./libs/primitive_plane.so", "getPrimitive"));

    RayTracer::Scene::i->ObjectHead->AddChildren(
        dlLoader<Prim>::getLib("./libs/light_spot.so", "getLight"));
    RayTracer::Scene::i->ObjectHead->AddChildren(
        dlLoader<Prim>::getLib("./libs/light_spot.so", "getLight"));
    RayTracer::Scene::i->ObjectHead->AddChildren(
        dlLoader<Prim>::getLib("./libs/primitive_sphere.so", "getPrimitive"));
    RayTracer::Scene::i->ObjectHead->AddChildren(
        dlLoader<Prim>::getLib("./libs/light_spot.so", "getLight"));

    computeTreeValues(RayTracer::Scene::i->ObjectHead);
    generateImage(window, image);
    displayImage(window, image);
}

void testMain() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Ray Tracer");
    sf::Image image;
    image.create(WIDTH, HEIGHT, sf::Color::Black);

    try {
        setupAndRun(window, image);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

int main(int argc, char **argv) {
    RayTracer::Parsing parser;

    try {
        parser.parseArgs(argc, argv);
        RayTracer::Scene scene = parser.parseSceneFile();
        testMain();
    } catch (const RayTracer::Parsing::ParsingError &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
