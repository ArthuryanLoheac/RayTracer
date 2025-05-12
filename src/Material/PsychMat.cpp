#include <memory>

#include "Material/PsychMat.hpp"

extern "C" std::unique_ptr<RayTracer::I_Material> getMaterial() {
    return std::make_unique<PsychMat>();
}

void PsychMat::Init() {
}

sf::Color PsychMat::getColorAt(int x, int y) {
    (void) x;
    (void) y;
    sf::Color color(255, 255, 255);
    color.a = 10;
    return (color);
}
