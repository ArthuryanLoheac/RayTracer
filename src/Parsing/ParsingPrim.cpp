
#include <iostream>
#include <string>
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

static sf::Color parseColor(const libconfig::Setting &color) {
    int rgb[3] = {0, 0, 0};

    color.lookupValue("r", rgb[0]);
    color.lookupValue("g", rgb[1]);
    color.lookupValue("b", rgb[2]);
    return sf::Color(rgb[0], rgb[1], rgb[2]);
}

static std::shared_ptr<I_Material> parseMaterial(const libconfig::Setting &material) {
    std::unordered_map<std::string, std::any> settings;
    const libconfig::Setting &color = material.lookup("color");
    std::string materialName;
    int rgb[3] = {0, 0, 0};

    material.lookupValue("name", materialName);
    color.lookupValue("r", rgb[0]);
    color.lookupValue("g", rgb[1]);
    color.lookupValue("b", rgb[2]);
    settings["color"] = parseColor(material.lookup("color"));
    std::shared_ptr<I_Material> mat =
        Factory<RayTracer::I_Material>::i().create(materialName);
    mat->Init(settings);
    return mat;
}

void parseSphere(const libconfig::Setting &sphere) {
    std::shared_ptr<I_Primitive> sphereObj =
        Factory<RayTracer::I_Primitive>::i().create("sphere");
    std::unordered_map<std::string, std::any> settings;
    const libconfig::Setting &position = sphere.lookup("position");
    const libconfig::Setting &rotation = sphere.lookup("rotation");
    const libconfig::Setting &material = sphere.lookup("material");
    float radius = 0.0f;

    sphere.lookupValue("radius", radius);
    settings["position"] = parsePosition(position);
    settings["rotation"] = parseRotation(rotation);
    settings["radius"] = radius;
    settings["material"] = parseMaterial(material);
    sphereObj->Init(settings);
    Scene::i->ObjectHead->AddChildren(sphereObj);
}

void Parsing::parsePrimitive(const libconfig::Setting &setting) {
    try {
        const libconfig::Setting &primitives = setting.lookup("primitives");
        const libconfig::Setting &spheres = primitives.lookup("spheres");
        for (int i = 0; i < spheres.getLength(); i++) {
            const libconfig::Setting &sphere = spheres[i];
            parseSphere(sphere);
        }
    } catch (const libconfig::SettingNotFoundException &nfex) {
        throw ParsingError("Missing primitives in configuration file.");
    } catch (const libconfig::SettingTypeException &tex) {
        throw ParsingError("Invalid type for primitives in configuration file.");
    }
}

}  // namespace RayTracer
