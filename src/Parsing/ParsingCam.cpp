
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <libconfig.h++>

#include "Parsing/Parsing.hpp"
#include "Scene/Scene.hpp"
#include "Scene/Camera.hpp"

namespace RayTracer {

void Parsing::parseCamera(const libconfig::Setting &camera) {
    std::unordered_map<std::string, std::any> settings;
    int width = 800;
    int height = 600;
    double fov = 90.0;
    std::string path = "assets/skybox.jpg";

    if (camera.exists("resolution")) {
        const libconfig::Setting &resolution = camera.lookup("resolution");
        resolution.lookupValue("width", width);
        resolution.lookupValue("height", height);
    }
    camera.lookupValue("fov", fov);
    camera.lookupValue("skybox", path);
    if (width <= 0 || height <= 0 ||
        width > 8000 || height > 8000)
        throw ParsingError("Invalid resolution values");
    settings["width"] = width;
    settings["height"] = height;
    settings["position"] = parsePosition(camera);
    settings["rotation"] = parseRotation(camera);
    settings["fov"] = fov;
    settings["skybox"] = path;
    Camera::i().Init(settings);
}

}  // namespace RayTracer
