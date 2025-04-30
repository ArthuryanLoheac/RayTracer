#include <memory>

#include "Material/FlatMat.hpp"

extern "C" std::unique_ptr<RayTracer::I_Material> getMaterial() {
    return std::make_unique<FlatMat>();
}

void FlatMat::Init() {
}

sf::Color FlatMat::getColorAt(int x, int y) {
    (void) x;
    (void) y;
    return sf::Color(255, 1, 1);
}
