#include <memory>

#include "Material/ImageMat.hpp"
#include <iostream>

extern "C" std::unique_ptr<RayTracer::I_Material> getMaterial() {
    return std::make_unique<ImageMat>();
}

ImageMat::ImageMat() {
    Init();
}

void ImageMat::Init() {
    scale = RayTracer::Vector3D(1, 1, 0);
    rotation = RayTracer::Vector3D(0.5f, 0, 0);
    img = sf::Image();
    if (!img.loadFromFile("assets/imagess.jpeg")) {
        std::cerr << "Error loading image" << std::endl;
        img.create(100, 100, sf::Color(234, 58, 247));
    }
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
