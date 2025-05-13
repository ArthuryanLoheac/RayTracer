#pragma once
#include "Interfaces/Material/I_Material.hpp"
#include "3dDatas/Point3D.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class PerlinMat : public RayTracer::I_Material {
 private:
    RayTracer::Vector3D scale;
    RayTracer::Vector3D rotation;

    float Noise2D(float x, float y);
 public:
    PerlinMat();
    ~PerlinMat() override = default;

    void Init() override;
    sf::Color getColorAt(float u, float v) override;
};
