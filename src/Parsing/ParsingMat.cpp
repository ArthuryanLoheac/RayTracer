
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

static sf::Color parseColor(const libconfig::Setting &color) {
    float rgb[3] = {0.0f, 0.0f, 0.0f};

    color.lookupValue("r", rgb[0]);
    color.lookupValue("g", rgb[1]);
    color.lookupValue("b", rgb[2]);
    return sf::Color(rgb[0], rgb[1], rgb[2]);
}

static sf::Color parseTransparentColor(const libconfig::Setting &color) {
    float rgb[4] = {0.0f, 0.0f, 0.0f, 1.0f};

    color.lookupValue("r", rgb[0]);
    color.lookupValue("g", rgb[1]);
    color.lookupValue("b", rgb[2]);
    color.lookupValue("a", rgb[3]);
    return sf::Color(rgb[0], rgb[1], rgb[2], rgb[3]);
}

static Vector3D parseRotation(const libconfig::Setting &rotation) {
    float rot[3] = {0.0f, 0.0f, 0.0f};

    rotation.lookupValue("x", rot[0]);
    rotation.lookupValue("y", rot[1]);
    rotation.lookupValue("z", rot[2]);
    return Vector3D(rot[0], rot[1], rot[2]);
}

static Vector3D parseScale(const libconfig::Setting &scale) {
    float sc[3] = {1.0f, 1.0f, 1.0f};

    scale.lookupValue("x", sc[0]);
    scale.lookupValue("y", sc[1]);
    scale.lookupValue("z", sc[2]);
    return Vector3D(sc[0], sc[1], sc[2]);
}

std::shared_ptr<I_Material> Parsing::parseMaterial(
const libconfig::Setting &material) {
    std::unordered_map<std::string, std::any> settings;
    std::string materialName;

    material.lookupValue("name", materialName);
    if (materialName == "flat")
        settings["color"] = parseColor(material.lookup("color"));
    if (materialName == "trans")
        settings["color"] = parseTransparentColor(material.lookup("color"));
    if (materialName == "chess")
        parseChess(material, settings);
    if (materialName == "perlin")
        parsePerlin(material, settings);
    if (materialName == "image")
        parseImage(material, settings);
    std::shared_ptr<I_Material> mat = Factory<Mat>::i().create(materialName);
    mat->Init(settings);
    return mat;
}

}  // namespace RayTracer
