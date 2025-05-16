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
#include "Scene/Camera.hpp"
#include "DesignPatterns/Factory.hpp"
#include "Draw/skybox.hpp"

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

static int setupAndRun(my_Image &image,
    std::string sceneFile, bool noWindowMode) {
    RayTracer::Camera &cam = RayTracer::Camera::i();

    computeTreeValues(RayTracer::Scene::i->ObjectHead);
    if (noWindowMode) {
        return renderImage(image);
    }
    sf::RenderWindow window(sf::VideoMode(cam.image_width, cam.image_height),
        "Ray Tracer");
    for (int i = cam.image_width /2; i >= 8; i /= 2)
        generateImagePreview(window, image, i);
    return generateImage(window, image, sceneFile);
}

int testMain(std::string sceneFile, bool noWindowMode) {
    RayTracer::Camera &cam = RayTracer::Camera::i();
    my_Image image;
    image.image.create(cam.image_width, cam.image_height, sf::Color::Black);

    try {
         return setupAndRun(image, sceneFile, noWindowMode);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

int main(int argc, char **argv) {
    RayTracer::Parsing parser;
    RayTracer::Scene scene;
    int hasFileChanged = 2;
    RayTracer::Camera cam;
    skybox::i().setImage("assets/skybox.jpg");
    srand(time(NULL));

    while (hasFileChanged != 0) {
        try {
            parser.parseArgs(argc, argv);
            parser.parseSceneFile();
            hasFileChanged = testMain(argv[1], parser.noWindowMode);
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
