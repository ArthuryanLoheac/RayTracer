#include <iostream>
#include <string>
#include <unordered_map>

#include <libconfig.h++>

#include "Parsing/Parsing.hpp"

namespace RayTracer {

Point3D Parsing::parsePosition(const libconfig::Setting &setting) {
    float pos[3] = {0.0f, 0.0f, 0.0f};

    if (setting.exists("position")) {
        const libconfig::Setting &position = setting.lookup("position");
        position.lookupValue("x", pos[0]);
        position.lookupValue("y", pos[1]);
        position.lookupValue("z", pos[2]);
    }
    return Point3D(pos[0], pos[1], pos[2]);
}

Vector3D Parsing::parseRotation(const libconfig::Setting &setting) {
    float rot[3] = {0.0f, 0.0f, 0.0f};

    if (setting.exists("rotation")) {
        const libconfig::Setting &rotation = setting.lookup("rotation");
        rotation.lookupValue("x", rot[0]);
        rotation.lookupValue("y", rot[1]);
        rotation.lookupValue("z", rot[2]);
    }
    return Vector3D(rot[0], rot[1], rot[2]);
}

Point3D Parsing::parseScalePoint(const libconfig::Setting &setting) {
    float sc[3] = {1.0f, 1.0f, 1.0f};


    if (setting.exists("scale")) {
        const libconfig::Setting &scale = setting.lookup("scale");
        scale.lookupValue("x", sc[0]);
        scale.lookupValue("y", sc[1]);
        scale.lookupValue("z", sc[2]);
    }
    return Point3D(sc[0], sc[1], sc[2]);
}

Vector3D Parsing::parseScaleVector(const libconfig::Setting &setting) {
    float sc[3] = {1.0f, 1.0f, 1.0f};

    if (setting.exists("scale")) {
        const libconfig::Setting &scale = setting.lookup("scale");
        scale.lookupValue("x", sc[0]);
        scale.lookupValue("y", sc[1]);
        scale.lookupValue("z", sc[2]);
    }
    return Vector3D(sc[0], sc[1], sc[2]);
}

sf::Image Parsing::parseImage(const libconfig::Setting &setting) {
    std::string path = "";
    sf::Image img;

    setting.lookupValue("path", path);
    if (path == "" || !img.loadFromFile(path))
        img.create(100, 100, sf::Color(234, 58, 247));
    return img;
}

sf::Color Parsing::parseColor(const libconfig::Setting &setting) {
    int rgb[4] = {0, 0, 0, 255};

    if (setting.exists("color")) {
        const libconfig::Setting &color = setting.lookup("color");
        color.lookupValue("r", rgb[0]);
        color.lookupValue("g", rgb[1]);
        color.lookupValue("b", rgb[2]);
        color.lookupValue("a", rgb[3]);
    }
    return sf::Color(rgb[0], rgb[1], rgb[2], rgb[3]);
}

}  // namespace RayTracer
