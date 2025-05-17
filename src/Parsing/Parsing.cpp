#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <filesystem>

#include <libconfig.h++>

#include "Parsing/Parsing.hpp"
#include "Scene/Scene.hpp"
#include "DesignPatterns/Factory.hpp"

namespace RayTracer {

static void printHelp() {
    std::cout << "USAGE: ./rayTracer <SCENE_FILE> [-r]" << std::endl;
    std::cout << "  SCENE_FILE: scene configuration" << std::endl;
    std::cout << "  -r: run in no window mode" << std::endl;
}

void Parsing::parseArgs(int argc, char **argv) {
    if (argc == 1)
        throw ParsingError("Missing arguments.");
    if (argc >= 4)
        throw ParsingError("Too many arguments.");
    if (argc == 2 && std::string(argv[1]) == "-h") {
        printHelp();
        exit(0);
    }
    if (std::filesystem::exists(argv[1]) == false)
        throw ParsingError("File does not exist.");
    sceneFile = argv[1];
    if (argc == 3 && std::string(argv[2]) == "-r")
        noWindowMode = true;
    else if (argc == 3)
        throw ParsingError("Invalid argument.");
}

void Parsing::parseSceneFile() {
    libconfig::Config cfg;

    try {
        cfg.readFile(sceneFile.c_str());
        const libconfig::Setting &raytracer = cfg.lookup("raytracer");
            Scene::i->ObjectHead = Factory<Prim>::i().create("none");
        parseCamera(raytracer.lookup("camera"));
        parsePrimitives(raytracer.lookup("primitives"));
        parseLights(raytracer.lookup("lights"));
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
