
#include <iostream>
#include <string>
#include <libconfig.h++>

#include "Parsing/Parsing.hpp"
#include "Scene/Scene.hpp"
#include "DesignPatterns/Factory.hpp"

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

void Parsing::parseSceneFile() {
    libconfig::Config cfg;

    try {
        cfg.readFile(sceneFile.c_str());
        const libconfig::Setting &raytracer = cfg.lookup("raytracer");
            Scene::i->ObjectHead = Factory<RayTracer::I_Primitive>::i().create("none");
        // parseCamera(raytracer);
        parsePrimitive(raytracer);
        // parseLights(raytracer);
    } catch (const libconfig::FileIOException &fioex) {
        throw ParsingError("I/O error while reading file.");
    } catch (const libconfig::ConfigException &ex) {
        throw ParsingError("Error in configuration file.");
    }
}

Parsing::ParsingError::ParsingError(const std::string &message)
: message("ParsingError: " + message) {}

const char *Parsing::ParsingError::what() const noexcept {
    return message.c_str();
}

}  // namespace RayTracer
