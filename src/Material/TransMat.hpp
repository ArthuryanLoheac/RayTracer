#pragma once
#include "Interfaces/Material/I_Material.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class TransMat : public RayTracer::I_Material {
 public:
    TransMat() = default;
    ~TransMat() override = default;

    void Init() override;
    sf::Color getColorAt(int x, int y) override;
};
