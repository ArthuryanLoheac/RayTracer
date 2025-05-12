#pragma once
#include "Interfaces/Material/I_Material.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class PsychMat : public RayTracer::I_Material {
 public:
    PsychMat() = default;
    ~PsychMat() override = default;

    void Init() override;
    sf::Color getColorAt(float x, float y) override;
};
