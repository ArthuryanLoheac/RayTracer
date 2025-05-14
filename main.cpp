#include <dlfcn.h>
#include <dirent.h>

#include <memory>
#include <vector>
#include <chrono>
#include <thread>
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

static void waitForFileModification(std::string sceneFile) {
    while (true) {
        if (hasFileChanged(sceneFile)) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

static int setupAndRun(sf::RenderWindow &window, my_Image &image,
    std::string sceneFile) {
    RayTracer::Scene::i->ObjectHead = Factory<Prim>::i().create("none");

    RayTracer::Scene::i->ObjectHead->AddChildren(
        Factory<Prim>::i().create("ambient"));
    RayTracer::Scene::i->ObjectHead->AddChildren(Factory<Prim>::i().
        create("spot"));
    RayTracer::Scene::i->ObjectHead->AddChildren(Factory<Prim>::i().
        create("spot"));
    RayTracer::Scene::i->ObjectHead->AddChildren(Factory<Prim>::i().
        create("spot"));
    RayTracer::Scene::i->ObjectHead->AddChildren(Factory<Prim>::i().
        create("cone"));
    RayTracer::Scene::i->ObjectHead->AddChildren(Factory<Prim>::i().
        create("plane"));
    RayTracer::Scene::i->ObjectHead->AddChildren(Factory<Prim>::i().
        create("cylinder"));
    RayTracer::Scene::i->ObjectHead->AddChildren(Factory<Prim>::i().
        create("sphere"));
    RayTracer::Scene::i->ObjectHead->AddChildren(Factory<Prim>::i().
        create("sphere"));

    computeTreeValues(RayTracer::Scene::i->ObjectHead);
    for (int i = WIDTH /2; i >= 8; i /= 2)
        generateImagePreview(window, image, i);
    printf("END FIRST DRAW\n");
    return generateImage(window, image, sceneFile);
}

int testMain(std::string sceneFile) {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Ray Tracer");
    my_Image image;
    image.image.create(WIDTH, HEIGHT, sf::Color::Black);

    try {
         return setupAndRun(window, image, sceneFile);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

int main(int argc, char **argv) {
    RayTracer::Parsing parser;
    int hasFileChanged = 2;
    srand(time(NULL));

    while (hasFileChanged != 0) {
        try {
            parser.parseArgs(argc, argv);
            RayTracer::Scene scene = parser.parseSceneFile();
            hasFileChanged = testMain(argv[1]);
        }
        catch (const RayTracer::Parsing::ParsingError &e) {
            std::cerr << e.what() << std::endl;
            if (hasFileChanged == 2)
                return 84;
            waitForFileModification(argv[1]);
        }
    }
    return 0;
}
