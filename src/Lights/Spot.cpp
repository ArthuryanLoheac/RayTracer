#include <memory>

#include "Lights/Spot.hpp"

extern "C" std::unique_ptr<RayTracer::I_Light> getLight() {
    return std::make_unique<Spot>();
}

Spot::Spot() {
    Init();
}

void Spot::Init() {
    angle = 70;
    intensity = 50.f;
    position = RayTracer::Point3D(10, 2, 20);
    rotation = RayTracer::Point3D(1, 0, 0);
}

float Spot::getLuminescence(float distance, float angle) {
    if (angle > this->angle)
        return 0;
    return intensity / std::pow(distance, 2);
}

bool Spot::hits(RayTracer::Ray ray, RayTracer::Point3D &intersection) {
    (void) ray;
    (void) intersection;
    return false;
}
