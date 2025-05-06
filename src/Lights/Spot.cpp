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
    intensity = 20.f;
    position = RayTracer::Point3D(0, 0, 20);
    rotation = RayTracer::Point3D(1, 0, 0);
}

float Spot::getLuminescence(float angle, float distance) {
    if (angle > this->angle)
        return 0;
    return intensity / std::pow(distance, 2);
}
