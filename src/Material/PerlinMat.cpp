#include <memory>

#include "Material/PerlinMat.hpp"

extern "C" std::unique_ptr<RayTracer::I_Material> getMaterial() {
    return std::make_unique<PerlinMat>();
}

PerlinMat::PerlinMat() {
    Init();
}

void PerlinMat::Init() {
    scale = RayTracer::Vector3D(1, 1, 0);
    rotation = RayTracer::Vector3D(0, 0, 0);
}

sf::Color PerlinMat::getColorAt(float u, float v) {
    if (scale.x == 0 || scale.y == 0)
        return sf::Color(234, 58, 247);  // error pink
    u /= scale.x;
    v /= -scale.y;
    if (u < 0) u = 1 + u;
    if (v < 0) v = 1 + v;
    u = fmod(u + rotation.x, 1);
    v = fmod(v + rotation.y, 1);
    if (u < 0) u = 1 + u;
    if (v < 0) v = 1 + v;

    float n = Noise2D(u, v);

    n += 1.0;
    n /= 2.0;

    int c = round(255*n);
    return sf::Color(c, c, c);
}

float PerlinMat::Noise2D(float x, float y) {
    (void) x;
    (void) y;
    return 0;
}