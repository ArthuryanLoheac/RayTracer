#include <memory>

#include "Material/FlatMat.hpp"

extern "C" std::unique_ptr<RayTracer::I_Material> getMaterial() {
    return std::make_unique<FlatMat>();
}

void FlatMat::Init() {
    col = sf::Color(255, 255, 255);
}

sf::Color FlatMat::getColorAt(float u, float v, RayTracer::Point3D point) {
    (void) u;
    (void) v;
    (void) point;
    return col;
}
