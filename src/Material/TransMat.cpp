#include <memory>
#include <string>

#include "Material/TransMat.hpp"

extern "C" std::unique_ptr<RayTracer::I_Material> getMaterial() {
    return std::make_unique<TransMat>();
}

void TransMat::Init(std::unordered_map<std::string, std::any> &settings) {
    (void)settings;
}

sf::Color TransMat::getColorAt(float x, float y) {
    (void)x;
    (void)y;
    return sf::Color(255, 255, 255, 125);
}
