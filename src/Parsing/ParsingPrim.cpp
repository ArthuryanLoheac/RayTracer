
#include <iostream>
#include <string>
#include <libconfig.h++>

#include "Parsing/Parsing.hpp"
#include "Scene/Scene.hpp"
#include "DesignPatterns/Factory.hpp"
#include "Primitive/PrimSphere.hpp"

namespace RayTracer {

void parseSphere(const libconfig::Setting &sphere) {
    std::shared_ptr<I_Primitive> sphereObj = Factory::i().create("sphere");
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
