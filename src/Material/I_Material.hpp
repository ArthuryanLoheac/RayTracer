#pragma once
#include <SFML/Graphics.hpp>

namespace RayTracer {
class I_Material {
 public:
    virtual ~I_Material() = default;
    virtual void Init() = 0;
    virtual sf::Color getColorAt(int x, int y) = 0;
};
} // namespace RayTracer

// extern "C" std::unique_ptr<RayTracer::I_Material> getMaterial();