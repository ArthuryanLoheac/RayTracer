#include <memory>

#include "Material/FlatMat.hpp"

extern "C" std::unique_ptr<RayTracer::I_Material> getMaterial() {
    return std::make_unique<FlatMat>();
}

FlatMat::FlatMat() {
    Init();
}

void FlatMat::Init() {
    col = sf::Color(0, 255, 155);
}

sf::Color FlatMat::getColorAt(float u, float v) {
    (void) u;
    (void) v;
    return col;
}
