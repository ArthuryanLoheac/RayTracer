
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

void Parsing::parseLight(const libconfig::Setting &light,
const std::string &type) {
    std::shared_ptr<I_Primitive> lightObj =
        Factory<Prim>::i().create(type);
    std::unordered_map<std::string, std::any> settings;
    float angle = 0.0f;
    float intensity = 0.0f;

    light.lookupValue("angle", angle);
    light.lookupValue("intensity", intensity);
    settings["position"] = parsePosition(light);
    settings["rotation"] = parseRotation(light);
    settings["scale"] = parseScalePoint(light);
    settings["color"] = parseColor(light);
    settings["angle"] = angle;
    settings["intensity"] = intensity;
    lightObj->Init(settings);
    Scene::i->ObjectHead->AddChildren(lightObj);
}

void Parsing::parseAmbiant(const libconfig::Setting &ambient) {
    for (int i = 0; i < ambient.getLength(); i++) {
        const libconfig::Setting &light = ambient[i];
        parseLight(light, "ambient");
    }
}

void Parsing::parseSpot(const libconfig::Setting &spot) {
    for (int i = 0; i < spot.getLength(); i++) {
        const libconfig::Setting &light = spot[i];
        parseLight(light, "spot");
    }
}

void Parsing::parseLights(const libconfig::Setting &lights) {
    if (lights.exists("ambient"))
        parseAmbiant(lights.lookup("ambient"));
    if (lights.exists("spot"))
        parseSpot(lights.lookup("spot"));
}

}  // namespace RayTracer
