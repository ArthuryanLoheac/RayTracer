#include <memory>

#include "Material/TransMat.hpp"

extern "C" std::unique_ptr<RayTracer::I_Material> getMaterial() {
    return std::make_unique<TransMat>();
}

void TransMat::Init() {
}

sf::Color TransMat::getColorAt(float x, float y) {
    (void) x;
    (void) y;
    sf::Color color(255, 255, 255);
    color.a = 127;
    return (color);
}
