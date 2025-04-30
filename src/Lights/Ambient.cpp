#include "Lights/Ambient.hpp"

extern "C" std::unique_ptr<RayTracer::I_Light> getLight() {
    return std::make_unique<Ambient>();
}

void Ambient::Init() {
    angle = 360;
    intensity = 1;
    position = RayTracer::Point3D(0, 0, 0);
}

float Ambient::getLuminescence(float distance, float angle) {
    (void) angle;
    return intensity / distance;
}

bool Ambient::hits(RayTracer::Ray ray) {
    (void) ray;
    return false;
}
