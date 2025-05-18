
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

static sf::Color parseColor1(const libconfig::Setting &setting) {
    int rgb[4] = {0, 0, 0, 255};

    if (setting.exists("color1")) {
        const libconfig::Setting &color = setting.lookup("color1");
        color.lookupValue("r", rgb[0]);
        color.lookupValue("g", rgb[1]);
        color.lookupValue("b", rgb[2]);
        color.lookupValue("a", rgb[3]);
    }
    return sf::Color(rgb[0], rgb[1], rgb[2], rgb[3]);
}

static sf::Color parseColor2(const libconfig::Setting &setting) {
    int rgb[4] = {0, 0, 0, 255};

    if (setting.exists("color2")) {
        const libconfig::Setting &color = setting.lookup("color2");
        color.lookupValue("r", rgb[0]);
        color.lookupValue("g", rgb[1]);
        color.lookupValue("b", rgb[2]);
        color.lookupValue("a", rgb[3]);
    }
    return sf::Color(rgb[0], rgb[1], rgb[2], rgb[3]);
}

std::shared_ptr<I_Material> Parsing::parseMaterial(
const libconfig::Setting &setting) {
    std::unordered_map<std::string, std::any> settings;
    std::string type = "flat";
    int octave = 0;
    float shininess = 0.0f;
    float specular = 0.0f;

    if (!setting.exists("material"))
        throw ParsingError("Missing material section.");
    const libconfig::Setting &material = setting.lookup("material");
    material.lookupValue("type", type);
    material.lookupValue("octave", octave);
    material.lookupValue("shininess", shininess);
    material.lookupValue("specular", specular);
    settings["color"] = parseColor(material);
    settings["color1"] = parseColor1(material);
    settings["color2"] = parseColor2(material);
    settings["scale"] = parseScaleVector(material);
    settings["rotation"] = parseRotation(material);
    settings["image"] = parseImage(material);
    settings["octave"] = octave;
    settings["shininess"] = shininess;
    settings["specular"] = specular;
    std::shared_ptr<I_Material> mat = Factory<Mat>::i().create(type);
    mat->Init(settings);
    return mat;
}

}  // namespace RayTracer
