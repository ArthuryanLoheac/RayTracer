#include <memory>

#include "Lights/Spot.hpp"

extern "C" std::unique_ptr<RayTracer::I_Light> getLight() {
    return std::make_unique<Spot>();
}

Spot::Spot() {
    Init();
}

void Spot::Init() {
    angle = 360;
    intensity = 2.f;
    position = RayTracer::Point3D(0, 0, 15);
    rotation = RayTracer::Point3D(1, 0, 0);
}

float Spot::getLuminescence(float angle) {
    (void) angle;
    return intensity;
}

bool Spot::hits(RayTracer::Ray ray, RayTracer::Point3D &intersection) {
    (void) ray;
    (void) intersection;
    return false;
}
