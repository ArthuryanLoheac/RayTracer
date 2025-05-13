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
#include "DesignPatterns/Factory.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

static void setupAndRun(sf::RenderWindow &window, my_Image &image) {
    RayTracer::Scene::i->ObjectHead = Factory::i().create("none");

    RayTracer::Scene::i->ObjectHead->AddChildren(Factory::i().create("ambient"));
    RayTracer::Scene::i->ObjectHead->AddChildren(Factory::i().create("spot"));
    RayTracer::Scene::i->ObjectHead->AddChildren(Factory::i().create("spot"));
    RayTracer::Scene::i->ObjectHead->AddChildren(Factory::i().create("spot"));

    RayTracer::Scene::i->ObjectHead->AddChildren(Factory::i().create("plane"));
    RayTracer::Scene::i->ObjectHead->AddChildren(Factory::i().create("cone"));

    computeTreeValues(RayTracer::Scene::i->ObjectHead);
    generateImage(window, image);
}

void testMain() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Ray Tracer");
    my_Image image;
    image.image.create(WIDTH, HEIGHT, sf::Color::Black);

    try {
        setupAndRun(window, image);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}

int main(int argc, char **argv) {
    RayTracer::Parsing parser;
    Factory factory;

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
