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
    intensity = 0.8f;
    position = RayTracer::Point3D(1.8f, 2.f, -28.f);
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
