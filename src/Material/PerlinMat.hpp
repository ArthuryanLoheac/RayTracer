#pragma once
#include <vector>
#include <string>

#include "Interfaces/Material/I_Material.hpp"
#include "3dDatas/Point3D.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class PerlinMat : public RayTracer::I_Material {
 private:
    RayTracer::Vector3D scale;
    RayTracer::Vector3D rotation;
    sf::Color c1, c2;
    std::vector<float> Permutation;
    int octave;

    float Noise2D(float x, float y);
    float Fade(float t);
    float Lerp(float t, float a1, float a2);
    std::vector<float> MakePermutation();
    void Shuffle(std::vector<float> &arrayToShuffle);
    RayTracer::Vector3D GetConstantVector(int v);

 public:
    PerlinMat();
    ~PerlinMat() override = default;

    void Init(std::unordered_map<std::string, std::any> &settings) override;
    sf::Color getColorAt(float u, float v) override;
    bool isReflective() const override;
};
