#pragma once
#include <any>
#include <string>
#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "3dDatas/Point3D.hpp"

namespace RayTracer {
class I_Material {
 public:
    virtual ~I_Material() = default;
    virtual void Init(std::unordered_map<std::string, std::any> &settings) = 0;
    virtual sf::Color getColorAt(float u, float v) = 0;
    virtual bool isReflective() const = 0;
    virtual float getSpecular() const = 0;
    virtual float getShininess() const = 0;
};
}  // namespace RayTracer

// extern "C" std::unique_ptr<RayTracer::I_Material> getMaterial();
