#include <memory>
#include <string>

#include "Material/FlatMat.hpp"

extern "C" std::unique_ptr<RayTracer::I_Material> getMaterial() {
    return std::make_unique<FlatMat>();
}

FlatMat::FlatMat() {
}

void FlatMat::Init(std::unordered_map<std::string, std::any> &settings) {
    col = std::any_cast<sf::Color>(settings["color"]);
}

sf::Color FlatMat::getColorAt(float u, float v) {
    (void) u;
    (void) v;
    return col;
}

bool FlatMat::isReflective() const {
    return false;
}

float FlatMat::getSpecular() const {
    return specular;
}

float FlatMat::getShininess() const {
    return shininess;
}

