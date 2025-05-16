#pragma once
#include <string>
#include "Interfaces/Material/I_Material.hpp"
#include "3dDatas/Point3D.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class ImageMat : public RayTracer::I_Material {
 private:
    float shininess = 2;
    float specular = 0.1;
    sf::Image img;
    RayTracer::Vector3D scale;
    RayTracer::Vector3D rotation;
 public:
    ImageMat();
    ~ImageMat() override = default;

    void Init(std::unordered_map<std::string, std::any> &settings) override;
    sf::Color getColorAt(float u, float v) override;
    bool isReflective() const override;
    float getSpecular() const override;
    float getShininess() const override;
};
