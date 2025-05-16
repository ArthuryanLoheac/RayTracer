#pragma once
#include <string>

#include "Interfaces/Material/A_Material.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class TransMat : public RayTracer::A_Material {
 private:
    sf::Color col;
 public:
    TransMat() = default;
    ~TransMat() override = default;

    void Init(std::unordered_map<std::string, std::any> &settings) override;
    sf::Color getColorAt(float x, float y) override;
};
