#pragma once
#include <string>

#include "Interfaces/Material/I_Material.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class TransMat : public RayTracer::I_Material {
 private:
    sf::Color col;
    float shininess = 50;
    float specular = 0.2;
 public:
    TransMat() = default;
    ~TransMat() override = default;

    void Init(std::unordered_map<std::string, std::any> &settings) override;
    sf::Color getColorAt(float x, float y) override;
    bool isReflective() const override;
    float getSpecular() const override;
    float getShininess() const override;
};
