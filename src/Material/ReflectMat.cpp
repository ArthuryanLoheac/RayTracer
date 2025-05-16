#include <memory>
#include <string>

#include "Material/ReflectMat.hpp"

extern "C" std::unique_ptr<RayTracer::I_Material> getMaterial() {
    return std::make_unique<ReflectMat>();
}

void ReflectMat::Init(std::unordered_map<std::string, std::any> &settings) {
    (void)settings;
    setNormal(std::any_cast<std::string>(settings["normal"]));
}

sf::Color ReflectMat::getColorAt(float x, float y) {
    (void)x;
    (void)y;
    return sf::Color(255, 255, 255, 255);
}

bool ReflectMat::isReflective() const {
    return true;
}
