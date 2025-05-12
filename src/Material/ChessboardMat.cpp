#include <memory>

#include "Material/ChessboardMat.hpp"
#include "ChessboardMat.hpp"

extern "C" std::unique_ptr<RayTracer::I_Material> getMaterial() {
    return std::make_unique<ChessboardMat>();
}

ChessboardMat::ChessboardMat() {
    Init();
}

void ChessboardMat::Init() {
    scale = RayTracer::Vector3D(20, 6, 0);
    col1 = sf::Color(255, 255, 255);
    col2 = sf::Color(0, 0, 0);
}

sf::Color ChessboardMat::getColorAt(float u, float v) {
    int u2 = floor(u * scale.x);
    int v2 = floor(v * scale.y);

    if ((u2 + v2) % 2 == 0)
        return col1;
    else
        return col2;
}
