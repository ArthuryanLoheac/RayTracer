#include "Lights/Ambient.hpp"

extern "C" std::unique_ptr<RayTracer::I_Light> getLight() {
    return std::make_unique<Ambient>();
}

Ambient::Ambient() {
    Init();
}

void Ambient::Init() {
    angle = 360;
    intensity = 10.3f;
    position = RayTracer::Point3D(0, 0, 0);
}

float Ambient::getLuminescence(float distance, float angle) {
    (void) angle;
    return intensity / (distance * distance);
}

bool Ambient::hits(RayTracer::Ray ray) {
    (void) ray;
    return false;
}
