
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <libconfig.h++>

#include "Parsing/Parsing.hpp"
#include "Scene/Scene.hpp"
#include "DesignPatterns/Factory.hpp"
#include "Primitive/PrimSphere.hpp"

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

static Point3D parseScale(const libconfig::Setting &scale) {
    float sc[3] = {1.0f, 1.0f, 1.0f};

    scale.lookupValue("x", sc[0]);
    scale.lookupValue("y", sc[1]);
    scale.lookupValue("z", sc[2]);
    return Point3D(sc[0], sc[1], sc[2]);
}

static sf::Color parseColor(const libconfig::Setting &color) {
    int rgb[3] = {0, 0, 0};

    color.lookupValue("r", rgb[0]);
    color.lookupValue("g", rgb[1]);
    color.lookupValue("b", rgb[2]);
    return sf::Color(rgb[0], rgb[1], rgb[2]);
}

void Parsing::parseLight(const libconfig::Setting &light,
const std::string &type) {
    std::shared_ptr<I_Primitive> lightObj =
        Factory<Prim>::i().create(type);
    std::unordered_map<std::string, std::any> settings;
    float angle = 180.0f;
    float intensity = 0.2f;

    light.lookupValue("angle", angle);
    light.lookupValue("intensity", intensity);

    try {
        settings["position"] = parsePosition(light.lookup("position"));
    }
    catch(const libconfig::SettingNotFoundException &e) {
        settings["position"] = Point3D(0.0f, 0.0f, 0.0f);
    }
    try {
        settings["rotation"] = parseRotation(light.lookup("rotation"));
    }
    catch(const libconfig::SettingNotFoundException &e) {
        settings["rotation"] = Vector3D(0.0f, 1.0f, 0.0f);
    }
    try {
        settings["scale"] = parseScale(light.lookup("scale"));
    }
    catch(const libconfig::SettingNotFoundException &e) {
        settings["scale"] = Point3D(1.0f, 1.0f, 1.0f);
    }
    try {
        settings["color"] = parseColor(light.lookup("color"));
    }
    catch(const libconfig::SettingNotFoundException &e) {
        settings["color"] = sf::Color(255, 0, 0);
    }
    settings["angle"] = angle;
    settings["intensity"] = intensity;
    lightObj->Init(settings);
    Scene::i->ObjectHead->AddChildren(lightObj);
}

void Parsing::parseLights(const libconfig::Setting &lights) {
    try {
        try {
            const libconfig::Setting &ambient = lights.lookup("ambient");
            for (int i = 0; i < ambient.getLength(); i++) {
                const libconfig::Setting &light = ambient[i];
                parseLight(light, "ambient");
            }
        }
        catch(const libconfig::SettingNotFoundException &e) {
        }
        try {
            const libconfig::Setting &spot = lights.lookup("spot");
            for (int i = 0; i < spot.getLength(); i++) {
                const libconfig::Setting &light = spot[i];
                parseLight(light, "spot");
            }
        }
        catch(const libconfig::SettingNotFoundException &e) {
        }
    } catch (const libconfig::SettingNotFoundException &nfex) {
        throw ParsingError("Missing primitives in configuration file.");
    } catch (const libconfig::SettingTypeException &tex) {
        throw ParsingError("Invalid primitives type in configuration file.");
    }
}

}  // namespace RayTracer
