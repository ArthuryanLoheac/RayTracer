#include "Interfaces/Material/A_Material.hpp"

namespace RayTracer {
bool A_Material::isReflective() const {
    return false;
}

void A_Material::setNormal(std::string path) {
    try {
        if (path == "")
            throw MaterialError("No normal map");
        if (!img.loadFromFile(path)) {
            throw MaterialError("Failed to load normal map from file: " + path);
        }
        hasNormal = true;
    } catch (std::exception &e) {
        hasNormal = false;
    }
}

Vector3D A_Material::getNormalAt(float u, float v) {
    if (!hasNormal) {
        return Vector3D(0, 0, 0);
    } else {
        float u2 = fmod(u, 1.0f);
        float v2 = fmod(v, 1.0f);
        int pixelX = static_cast<int>(u2 * img.getSize().x);
        if (pixelX < 0) pixelX += img.getSize().x;
        int pixelY = static_cast<int>(v2* img.getSize().y);
        if (pixelY < 0) pixelY += img.getSize().y;

        sf::Color c = img.getPixel(pixelX, pixelY);
        return  Vector3D(
            ((c.r / 255.f) * 2.f) - 1.f,
            ((c.g / 255.f) * 2.f) - 1.f,
            ((c.b / 255.f) * 2.f) - 1.f);
    }
}

}
