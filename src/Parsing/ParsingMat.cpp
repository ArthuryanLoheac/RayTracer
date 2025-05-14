
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
