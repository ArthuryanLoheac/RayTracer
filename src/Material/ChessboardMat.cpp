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
    Inv_scale = 10;
    col1 = sf::Color(255, 255, 255);
    col2 = sf::Color(255, 0, 0);
}

sf::Color ChessboardMat::getColorAt(float u, float v, RayTracer::Point3D point) {
    (void) u;
    (void) v;
    int x = std::floor(Inv_scale * point.x);
    int y = std::floor(Inv_scale * point.y);
    int z = std::floor(Inv_scale * point.z);

    bool is_even = (x + y + z) % 2 == 0;

    if (is_even) {
        return col1;
    } else {
        return col2;
    }
}
