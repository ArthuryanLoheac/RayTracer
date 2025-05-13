#include <memory>

#include "Material/ImageMat.hpp"

extern "C" std::unique_ptr<RayTracer::I_Material> getMaterial() {
    return std::make_unique<ImageMat>();
}

ImageMat::ImageMat() {
    Init();
}

void ImageMat::Init() {
    scale = RayTracer::Vector3D(4, 4, 0);
    img = sf::Image();
    img.loadFromFile("assets/shrek-5.jpg");
}

sf::Color ImageMat::getColorAt(float u, float v) {
    if (u < 0) u = 1 + u;
    if (v < 0) v = 1 + v;
    u /= scale.x;
    v /= scale.y;
    int pixX = (int)(u * img.getSize().x);
    int pixY = (int)(v * img.getSize().y);
    return img.getPixel(pixX, pixY);
}
