#include <memory>

#include "Lights/Spot.hpp"

extern "C" std::unique_ptr<RayTracer::I_Light> getLight() {
    return std::make_unique<Spot>();
}

Spot::Spot() {
    Init();
}

void Spot::Init() {
    angle = 75;
    intensity = 1000.f;
    position = RayTracer::Point3D(15.5f, 30.5f, -730.f);
    rotation = RayTracer::Point3D(0,1.5f,0.5f);
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
