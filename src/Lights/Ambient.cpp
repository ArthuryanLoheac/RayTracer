#include <memory>

#include "Lights/Ambient.hpp"

extern "C" std::unique_ptr<RayTracer::I_Light> getLight() {
    return std::make_unique<Ambient>();
}

Ambient::Ambient() {
    Init();
}

void Ambient::Init() {
    angle = 360;
    intensity = 0.1f;
    position = RayTracer::Point3D(-0.15f, 0.45f, -2.f);
    color = sf::Color(255, 255, 255, 255);
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
