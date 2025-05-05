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
    intensity = 0.2f;
    position = RayTracer::Point3D(-0.15f, 0.45f, -2.f);
}

float Ambient::getLuminescence(float angle, float distance) {
    (void) angle;
    (void) distance;
    return intensity;
}

bool Ambient::hits(RayTracer::Ray ray, RayTracer::Point3D &intersection) {
    (void) ray;
    (void) intersection;
    return false;
}
