#pragma once
#include <string>
#include "Interfaces/Material/I_Material.hpp"
#include "3dDatas/Point3D.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class ChessboardMat : public RayTracer::I_Material {
 private:
    sf::Color col1;
    sf::Color col2;
    RayTracer::Vector3D scale;
 public:
    ChessboardMat();
    ~ChessboardMat() override = default;

    void Init(std::unordered_map<std::string, std::any> &settings) override;
    sf::Color getColorAt(float u, float v) override;
    bool isReflective() const override;
};
