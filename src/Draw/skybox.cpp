#include <cmath>
#include <string>

#include "Draw/skybox.hpp"
#include "Consts/const.hpp"

void skybox::setColor(sf::Color color) {
    isImage = false;
    cl = color;
}

void skybox::setImage(std::string path) {
    try {
        if (!img.loadFromFile(path)) {
            throw skyboxException("Failed to load skybox image");
        }
        isImage = true;
    } catch (std::exception &e) {
        isImage = false;
        cl = PINK_ERROR;
    }
}

skybox::skybox() {
    isImage = false;
    cl = sf::Color(0, 0, 0);
}

sf::Color skybox::getColorAt(RayTracer::Vector3D vec) {
    if (isImage) {
        vec.x = std::fmod(vec.x, 1);
        vec.y = std::fmod(vec.y, 1);
        int pixelX = static_cast<int>(vec.x * img.getSize().x);
        if (pixelX < 0)
            pixelX += img.getSize().x;
        int pixelY = static_cast<int>(vec.y * img.getSize().y);
        if (pixelY < 0)
            pixelY += img.getSize().y;
        return img.getPixel(pixelX, pixelY);
    } else {
        return cl;
    }
}

RayTracer::Vector3D skybox::getAngle(RayTracer::Ray r) {
    RayTracer::Vector3D dir = r.direction.normalized();
    dir.x = (dir.x + 1.f) /2.f;
    dir.y = (dir.y + 1.f) /2.f;
    return RayTracer::Vector3D(dir.x, -dir.y, 0);
}
