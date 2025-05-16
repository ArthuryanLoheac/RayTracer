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
    rotation = std::any_cast<RayTracer::Vector3D>(settings["rotation"]);
    scale = std::any_cast<RayTracer::Point3D>(settings["scale"]);
}

float Ambient::getLuminescence(hitDatas &datas,
    std::shared_ptr<I_Light> Light,
    std::shared_ptr<I_Primitive> head) {
    (void) Light;
    (void) datas;
    (void) head;
    return intensity;
}
