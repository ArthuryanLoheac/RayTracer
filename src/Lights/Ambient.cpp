#include <memory>
#include <string>

#include "Lights/Ambient.hpp"

extern "C" std::unique_ptr<RayTracer::I_Light> getLight() {
    return std::make_unique<Ambient>();
}

Ambient::Ambient() {
}

void Ambient::Init(std::unordered_map<std::string, std::any> &settings) {
    angle = std::any_cast<float>(settings["angle"]);
    intensity = std::any_cast<float>(settings["intensity"]);
    position = std::any_cast<RayTracer::Point3D>(settings["position"]);
    color = std::any_cast<sf::Color>(settings["color"]);
}

float Ambient::getLuminescence(RayTracer::Point3D intersection,
std::shared_ptr<I_Light> Light, std::shared_ptr<I_Primitive> obj,
std::shared_ptr<I_Primitive> head) {
    (void) intersection;
    (void) Light;
    (void) obj;
    (void) head;
    return intensity;
}
