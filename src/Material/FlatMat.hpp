#pragma once
#include "Interfaces/Material/I_Material.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class FlatMat : public RayTracer::I_Material {
 public:
    FlatMat() = default;
    ~FlatMat() override = default;

    void Init() override;
    sf::Color getColorAt(int x, int y) override;
};
