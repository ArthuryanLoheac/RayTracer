#pragma once
#include <string>

#include "Interfaces/Material/I_Material.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class ReflectMat : public RayTracer::I_Material {
 private:
    float shininess = 1;
    float specular = 200;
 public:
    ReflectMat() = default;
    ~ReflectMat() override = default;

    void Init(std::unordered_map<std::string, std::any> &settings) override;
    sf::Color getColorAt(float x, float y) override;
    bool isReflective() const override;
    float getSpecular() const override;
    float getShininess() const override;
};
