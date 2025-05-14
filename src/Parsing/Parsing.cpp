
#include <iostream>
#include <string>
#include <filesystem>
#include <libconfig.h++>

#include "Parsing/Parsing.hpp"
#include "Scene/Scene.hpp"

namespace RayTracer {

void Parsing::parseArgs(int argc, char **argv) {
    noWindowMode = false;
    if (argc < 2)
        throw ParsingError("Missing arguments.");
    if (std::string(argv[1]) == "-help") {
        std::cout << "USAGE: ./rayTracer <SCENE_FILE>" << std::endl;
        std::cout << "  SCENE_FILE: scene configuration" << std::endl;
        exit(0);
    }
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-r") {
            noWindowMode = true;
            continue;
        }
        if (std::filesystem::exists(argv[i])) {
            sceneFile = argv[i];
        } else {
            throw ParsingError("Invalid argument: " + std::string(argv[i]));
        }
    }
}

Scene Parsing::parseSceneFile() {
    RayTracer::Scene scene;
    libconfig::Config cfg;

    try {
        cfg.readFile(sceneFile.c_str());
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
