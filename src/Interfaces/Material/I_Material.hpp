#pragma once
#include <SFML/Graphics.hpp>

#include "3dDatas/Point3D.hpp"

namespace RayTracer {
class I_Material {
 public:
    virtual ~I_Material() = default;
    virtual void Init() = 0;
    virtual sf::Color getColorAt(float u, float v) = 0;
};
}  // namespace RayTracer

// extern "C" std::unique_ptr<RayTracer::I_Material> getMaterial();
