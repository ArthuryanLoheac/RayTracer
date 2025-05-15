#include <memory>
#include <string>

#include "Material/ReflectMat.hpp"

extern "C" std::unique_ptr<RayTracer::I_Material> getMaterial() {
    return std::make_unique<ReflectMat>();
}

void ReflectMat::Init(std::unordered_map<std::string, std::any> &settings) {
    color = std::any_cast<sf::Color>(settings["color"]);
    Reflectivity = std::any_cast<float>(settings["reflectivity"]) / 255.f;
    printf("Reflectivity: %f\n", Reflectivity);
}

sf::Color ReflectMat::getColorAt(float x, float y) {
    (void)x;
    (void)y;
    return color;
}

float ReflectMat::getReflective() const {
    // Alpha is used for percentage of reflection
    // 0 = no reflection, 1 = full reflection
    return Reflectivity;
}
