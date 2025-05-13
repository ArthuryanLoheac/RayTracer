#pragma once
#include "Interfaces/Material/I_Material.hpp"
#include "3dDatas/Point3D.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class PerlinMat : public RayTracer::I_Material {
 private:
    sf::Color col1;
    sf::Color col2;
    RayTracer::Vector3D scale;
 public:
    PerlinMat();
    ~PerlinMat() override = default;

    void Init() override;
    sf::Color getColorAt(float u, float v) override;
};
