#pragma once
#include "Interfaces/Material/I_Material.hpp"
#include "3dDatas/Point3D.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class FlatMat : public RayTracer::I_Material {
 private:
    sf::Color col;
 public:
    FlatMat();
    ~FlatMat() override = default;

    void Init() override;
    sf::Color getColorAt(float u, float v) override;
};
