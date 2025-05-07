
#include <iostream>
#include <string>
#include <libconfig.h++>

#include "Parsing/Parsing.hpp"
#include "Scene/Scene.hpp"

extern int WIDTH;
extern int HEIGHT;

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

double Parsing::getDouble(libconfig::Setting &setting) {
    switch (setting.getType()) {
        case libconfig::Setting::TypeFloat:
            return static_cast<double>(setting.operator float());
        case libconfig::Setting::TypeInt:
            return static_cast<double>(setting.operator int());
        default:
            throw ParsingError("Invalid type for double value.");
    }
}


void Parsing::parseCamera(Scene &scene, libconfig::Config &cfg) {
    // Check if the camera section exists

    (void)scene;

    if (!cfg.exists("camera"))
        throw ParsingError("Camera section not found in configuration file.");

    libconfig::Setting &camera = cfg.lookup("camera");

    if (camera.exists("resolution")) {
        try {
            libconfig::Setting &resolution = camera["resolution"];
            int width = resolution["width"];
            int height = resolution["height"];
            WIDTH = width;
            HEIGHT = height;
        } catch (std::exception &e) {
            throw ParsingError("Invalid camera resolution format.");
        }
    }

    if (camera.exists("position")) {
        try {
            libconfig::Setting &position = camera["position"];
            double x = getDouble(position["x"]);
            double y = getDouble(position["y"]);
            double z = getDouble(position["z"]);
            std::cout << "Camera position: (" << x << ", " << y << ", " << z
                        << ")" << std::endl;
        } catch (std::exception &e) {
            throw ParsingError("Invalid camera position format.");
        }
    }

    if (camera.exists("rotation")) {
        try {
            libconfig::Setting &rotation = camera["rotation"];
            double x = getDouble(rotation["x"]);
            double y = getDouble(rotation["y"]);
            double z = getDouble(rotation["z"]);
            std::cout << "Camera rotation: (" << x << ", " << y << ", " << z
                        << ")" << std::endl;
        } catch (std::exception &e) {
            throw ParsingError("Invalid camera rotation format.");
        }
    }

    if (camera.exists("fieldOfView")) {
        try {
            libconfig::Setting &fov = camera["fieldOfView"];
            double fovValue = getDouble(fov);
            std::cout << "Camera field of view: " << fovValue << " degrees"
                      << std::endl;
        } catch (libconfig::SettingTypeException &e) {
            throw ParsingError("Invalid field of view format.");
        }
    }
}

Scene Parsing::parseSceneFile() {
    RayTracer::Scene scene;
    libconfig::Config cfg;

    try {
        cfg.readFile(sceneFile.c_str());
    } catch (const libconfig::FileIOException &fioex) {
        throw ParsingError("I/O error while reading file.");
    } catch (const libconfig::ConfigException &ex) {
        throw ParsingError("Error in configuration file.");
    }
    try {
        parseCamera(scene, cfg);
    } catch (const ParsingError &e) {
        throw ParsingError("Error parsing camera section: " +
            std::string(e.what()));
    }
    return scene;
}

Parsing::ParsingError::ParsingError(const std::string &message)
: message(message) {}

const char *Parsing::ParsingError::what() const noexcept {
    return message.c_str();
}

}  // namespace RayTracer
