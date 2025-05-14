#include <memory>
#include <iostream>
#include <string>

#include "Material/ImageMat.hpp"

extern "C" std::unique_ptr<RayTracer::I_Material> getMaterial() {
    return std::make_unique<ImageMat>();
}

ImageMat::ImageMat() {
}

void ImageMat::Init(std::unordered_map<std::string, std::any> &settings) {
    scale = std::any_cast<RayTracer::Vector3D>(settings["scale"]);
    rotation = std::any_cast<RayTracer::Vector3D>(settings["rotation"]);
    img = std::any_cast<sf::Image>(settings["image"]);
}

sf::Color ImageMat::getColorAt(float u, float v) {
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
    int pixX = static_cast<int>(u * img.getSize().x);
    int pixY = static_cast<int>(v * img.getSize().y);
    return img.getPixel(pixX, pixY);
}
