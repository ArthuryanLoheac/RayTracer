#include <memory>
#include <string>

#include "Material/ReflectMat.hpp"

extern "C" std::unique_ptr<RayTracer::I_Material> getMaterial() {
    return std::make_unique<ReflectMat>();
}

void ReflectMat::Init(std::unordered_map<std::string, std::any> &settings) {
    shininess = std::any_cast<float>(settings["shininess"]);
    specular = std::any_cast<float>(settings["specular"]);
}

sf::Color ReflectMat::getColorAt(float x, float y) {
    (void)x;
    (void)y;
    return sf::Color(255, 255, 255, 255);
}

bool ReflectMat::isReflective() const {
    return true;
}

float ReflectMat::getSpecular() const {
    return specular;
}

float ReflectMat::getShininess() const {
    return shininess;
}

