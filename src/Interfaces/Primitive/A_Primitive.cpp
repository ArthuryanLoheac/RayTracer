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
        Vector3D toRotate = normal;
        Vector3D rotationToDo = material->getNormalAt(uv.x, uv.y);
        rotationToDo = Vector3D(
            rotationToDo.x * 180,
            rotationToDo.y * 180,
            rotationToDo.z * 180);
        return getRotatedVector(toRotate, rotationToDo);
    } catch (std::exception &e) {
        return normal;
    }
}

Vector3D A_Primitive::getRotatedVector(Vector3D vector, Vector3D rotationToDo) {
    Vector3D vec(vector.x, vector.y, vector.z);
    float rx = rotationToDo.x * M_PI / 180.0f;
    float ry = rotationToDo.y * M_PI / 180.0f;
    float rz = rotationToDo.z * M_PI / 180.0f;

    // Axe X
    vec = RayTracer::Vector3D(
        vec.x,
        vec.y * cos(rx) - vec.z * sin(rx),
        vec.y * sin(rx) + vec.z * cos(rx));

    // Axe Y
    vec = RayTracer::Vector3D(
        vec.x * cos(ry) + vec.z * sin(ry),
        vec.y,
        -vec.x * sin(ry) + vec.z * cos(ry));

    // Axe Z
    vec = RayTracer::Vector3D(
        vec.x * cos(rz) - vec.y * sin(rz),
        vec.x * sin(rz) + vec.y * cos(rz),
        vec.z);
    return vec;
}

A_Primitive::PrimitiveError::PrimitiveError(const std::string &message)
    : message("PrimitiveError: " + message) {}
}  // namespace RayTracer
