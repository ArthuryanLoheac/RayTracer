#include <memory>
#include <string>

#include "Material/ChessboardMat.hpp"

extern "C" std::unique_ptr<RayTracer::I_Material> getMaterial() {
    return std::make_unique<ChessboardMat>();
}

ChessboardMat::ChessboardMat() {
}

void ChessboardMat::Init(std::unordered_map<std::string, std::any> &settings) {
    scale = std::any_cast<RayTracer::Vector3D>(settings["scale"]);
    col1 = std::any_cast<sf::Color>(settings["col1"]);
    col2 = std::any_cast<sf::Color>(settings["col2"]);
}

sf::Color ChessboardMat::getColorAt(float u, float v) {
    int u2 = floor(u * scale.x);
    int v2 = floor(v * scale.y);

    if ((u2 + v2) % 2 == 0)
        return col1;
    else
        return col2;
}

bool ChessboardMat::isReflective() const {
    return false;
}
