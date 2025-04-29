#include <memory>

#include "Material/FlatMat.hpp"

extern "C" std::unique_ptr<RayTracer::I_Material> getMaterial() {
    return std::make_unique<FlatMat>();
}

void FlatMat::Init() {
    // Initialization code for FlatMat
}

sf::Color FlatMat::getColorAt(int x, int y) {
    // Return a color based on the coordinates (x, y)
    (void) x;
    (void) y;
    return sf::Color(255, 0, 0); 
}
