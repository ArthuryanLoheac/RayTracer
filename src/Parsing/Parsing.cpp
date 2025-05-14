
#include <iostream>
#include <string>
#include <filesystem>
#include <libconfig.h++>

#include "Parsing/Parsing.hpp"
#include "Scene/Scene.hpp"

namespace RayTracer {

void Parsing::parseArgs(int argc, char **argv) {
    noWindowMode = false;
    aa = 3;
    if (argc < 2)
        throw ParsingError("Missing arguments.");
    if (std::string(argv[1]) == "-help" || std::string(argv[1]) == "-h") {
        std::cout << "USAGE: ./rayTracer <SCENE_FILE> [-r] [-a=X]"
            << std::endl;
        std::cout << "  SCENE_FILE: scene configuration" << std::endl;
        std::cout << "  -r: run in no window mode" << std::endl;
        std::cout << "  -a=x: set the anti aliasing level to X(default: 3)"
            << std::endl;
        exit(0);
    }
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-r") {
            noWindowMode = true;
            continue;
        }
        if (std::string(argv[i]).find("-a=") == 0) {
            std::string aaStr = std::string(argv[i]).substr(3);
            try {
                aa = std::stoi(aaStr);
                if (aa < 1)
                    throw ParsingError("Invalid anti-aliasing level.");
            } catch (const std::invalid_argument &) {
                throw ParsingError("Invalid anti-aliasing level.");
            }
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
