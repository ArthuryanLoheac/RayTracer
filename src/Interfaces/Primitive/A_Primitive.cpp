#include <memory>
#include <vector>
#include <string>

#include "Interfaces/Primitive/A_Primitive.hpp"
#include "A_Primitive.hpp"
#include <iostream>

namespace RayTracer {

std::vector<std::shared_ptr<I_Primitive>>
&RayTracer::A_Primitive::getChildrens() {
    return childrens;
}

std::shared_ptr<I_Primitive> &RayTracer::A_Primitive::AddChildren(
std::shared_ptr<I_Primitive> child) {
    childrens.push_back(child);
    return childrens.back();
}

std::shared_ptr<I_Material> RayTracer::A_Primitive::getMaterial() {
    if (!material)
        throw PrimitiveError("Material not set");
    return material;
}

void A_Primitive::setMaterial(std::shared_ptr<I_Material> material) {
    this->material = material;
}

Point3D RayTracer::A_Primitive::getPosition() {
    return position;
}

void RayTracer::A_Primitive::setPosition(Point3D pos) {
    position = pos;
}

Vector3D RayTracer::A_Primitive::getRotation() {
    return rotation;
}

void RayTracer::A_Primitive::setRotation(Vector3D rot) {
    rotation = rot;
}

Point3D RayTracer::A_Primitive::getScale() {
    return scale;
}

void RayTracer::A_Primitive::setScale(Point3D scale) {
    this->scale = scale;
}

bool A_Primitive::returnCollision(float A, float B, float C,
Point3D &intersection, Ray &ray) {
    double d = B * B - 4 * A * C;

    if (d < 0)
        return false;
    float t1 = (-B - std::sqrt(d)) / (2 * A);
    float t2 = (-B + std::sqrt(d)) / (2 * A);
    float t = (t1 < t2) ? t1 : t2;
    if (t < 0)
        return false;
    intersection = ray.origin + ray.direction * t;
    return true;
}

Vector3D A_Primitive::rotatedNormal(Vector3D normal, RayTracer::Vector3D uv) {
    try {
        if (!material) {
            throw PrimitiveError("Material not set");
        }
        Vector3D tangent(1, 0, 0);  // Example tangent vector
        Vector3D bitangent(0, 1, 0);  // Example bitangent vector
        Vector3D normalMap = material->getNormalAt(uv.x, uv.y);
        return material->rotatedNormal(normal, normalMap, tangent, bitangent);
    } catch (std::exception &e) {
        return normal;
    }
}

Vector3D A_Primitive::getNormalAt(Point3D point) {
    return rotatedNormal(getRawNormalAt(point), getUV(point));
}

A_Primitive::PrimitiveError::PrimitiveError(const std::string &message)
    : message("PrimitiveError: " + message) {}
}  // namespace RayTracer
