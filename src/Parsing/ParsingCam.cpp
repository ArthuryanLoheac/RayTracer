
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <libconfig.h++>

#include "Parsing/Parsing.hpp"
#include "Scene/Scene.hpp"
#include "Scene/Camera.hpp"

namespace RayTracer {

static Point3D parsePosition(const libconfig::Setting &position) {
    float pos[3] = {0.0f, 0.0f, 0.0f};

    position.lookupValue("x", pos[0]);
    position.lookupValue("y", pos[1]);
    position.lookupValue("z", pos[2]);
    return Point3D(pos[0], pos[1], pos[2]);
}

static Vector3D parseRotation(const libconfig::Setting &rotation) {
    float rot[3] = {0.0f, 0.0f, 0.0f};

    rotation.lookupValue("x", rot[0]);
    rotation.lookupValue("y", rot[1]);
    rotation.lookupValue("z", rot[2]);
    return Vector3D(rot[0], rot[1], rot[2]);
}

void parseCam(const libconfig::Setting &camera) {
    const libconfig::Setting &resolution = camera.lookup("resolution");
    std::unordered_map<std::string, std::any> settings;
    int width = 800;
    int height = 800;
    double fov = 90.0;

    resolution.lookupValue("width", width);
    resolution.lookupValue("height", height);
    camera.lookupValue("fov", fov);
    settings["width"] = width;
    settings["height"] = height;
    try {
        settings["position"] = parsePosition(camera.lookup("position"));
    }
    catch(const libconfig::SettingNotFoundException &e) {
        settings["position"] = Point3D(0.0f, 0.0f, 0.0f);
    }
    try {
        settings["rotation"] = parseRotation(camera.lookup("rotation"));
    }
    catch(const libconfig::SettingNotFoundException &e) {
        settings["rotation"] = Vector3D(0.0f, 0.0f, 0.0f);
    }
    settings["fov"] = fov;
    Camera::i().Init(settings);
}

void Parsing::parseCamera(const libconfig::Setting &camera) {
    try {
        parseCam(camera);
    } catch (const libconfig::SettingNotFoundException &nfex) {
        throw ParsingError("Missing primitives in configuration file.");
    } catch (const libconfig::SettingTypeException &tex) {
        throw ParsingError("Invalid primitives type in configuration file.");
    }
}

}  // namespace RayTracer
