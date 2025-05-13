#pragma once
#include "Interfaces/Material/I_Material.hpp"
#include "3dDatas/Point3D.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class ImageMat : public RayTracer::I_Material {
 private:
    sf::Image img;
    RayTracer::Vector3D scale;
    RayTracer::Vector3D rotation;
 public:
    ImageMat();
    ~ImageMat() override = default;

    void Init() override;
    sf::Color getColorAt(float u, float v) override;
};
