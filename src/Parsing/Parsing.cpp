
#include <iostream>
#include <string>
#include <libconfig.h++>

#include "Parsing/Parsing.hpp"
#include "Scene/Scene.hpp"

namespace RayTracer {

void Parsing::parseArgs(int argc, char **argv) {
    if (argc < 2)
        throw ParsingError("Missing scene file argument.");
    if (argc > 2)
        throw ParsingError("Too many arguments.");
    if (std::string(argv[1]) == "-help") {
        std::cout << "USAGE: ./rayTracer <SCENE_FILE>" << std::endl;
        std::cout << "  SCENE_FILE: scene configuration" << std::endl;
        exit(0);
    }
    sceneFile = argv[1];
}

Scene Parsing::parseSceneFile() {
    RayTracer::Scene scene;
    libconfig::Config cfg;
    libconfig::Setting &root = cfg.getRoot();
    libconfig::Setting &raytracer = root["raytracer"];

    try {
        cfg.readFile(sceneFile.c_str());
        // parseCamera(raytracer["camera"], scene);
        parsePrimitive(raytracer["primitives"], scene);
        // parseLights(raytracer["lights"], scene);
        if (!cfg.exists("raytracer"))
            throw ParsingError("Missing 'raytracer' section in config file.");
    } catch (const libconfig::FileIOException &fioex) {
        throw ParsingError("I/O error while reading file.");
    } catch (const libconfig::ConfigException &ex) {
        throw ParsingError("Error in configuration file.");
    }
    return scene;
}

Parsing::ParsingError::ParsingError(const std::string &message)
: message("ParsingError: " + message) {}

const char *Parsing::ParsingError::what() const noexcept {
    return message.c_str();
}

}  // namespace RayTracer
