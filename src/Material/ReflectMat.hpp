#pragma once
#include <string>

#include "Interfaces/Material/A_Material.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class ReflectMat : public RayTracer::A_Material {
 public:
    ReflectMat() = default;
    ~ReflectMat() override = default;

    void Init(std::unordered_map<std::string, std::any> &settings) override;
    sf::Color getColorAt(float x, float y) override;
    bool isReflective() const override;
};
