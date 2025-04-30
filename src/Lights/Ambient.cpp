#include "Lights/Ambient.hpp"

extern "C" std::unique_ptr<RayTracer::I_Lights> getLight() {
    return std::make_unique<Ambient>();
}

void Ambient::Init() {
    angle = 360;
}

float Ambient::getLuminescence(float distance, float angle) {
    (void) angle;
    return 1 / distance;
}

bool Ambient::hits(RayTracer::Ray ray) {
    (void) ray;
    return false;
}
