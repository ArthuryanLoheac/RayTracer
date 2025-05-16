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
        if (u < 0) u = 1 + u;
        if (v < 0) v = 1 + v;
        u = fmod(u, 1);
        v = fmod(v, 1);
        if (u < 0) u = 1 + u;
        if (v < 0) v = 1 + v;
        int pixX = static_cast<int>(u * img.getSize().x);
        int pixY = static_cast<int>(v * img.getSize().y);

        sf::Color c = img.getPixel(pixX, pixY);
        return Vector3D(
            ((c.r / 255.f) * 2) - 1.f, // Adjust X component
            ((c.b / 255.f) * 2) - 1.f, // Add Y component
            ((c.g / 255.f) * 2) - 1.f  // Adjust Z component
        );
    }
}

Vector3D A_Material::rotatedNormal(const Vector3D &normal, Vector3D &normalMap, const Vector3D &tangent, const Vector3D &bitangent) const {
    // Normalize the input vectors
    Vector3D T = tangent.normalized();
    Vector3D B = bitangent.normalized();
    Vector3D N = normal.normalized();
    
    // Manually compute the transformation from tangent space to world space
    // This is equivalent to multiplying by the TBN matrix
    Vector3D rotated(
        normalMap.x * T.x + normalMap.y * B.x + normalMap.z * N.x,
        normalMap.x * T.y + normalMap.y * B.y + normalMap.z * N.y,
        normalMap.x * T.z + normalMap.y * B.z + normalMap.z * N.z
    );
    
    return rotated.normalize(); // Return the normalized rotated normal
}

}
