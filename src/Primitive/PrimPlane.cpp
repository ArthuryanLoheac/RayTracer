#include <cmath>
#include <string>
#include <iostream>
#include <memory>

#include "Primitive/PrimPlane.hpp"
#include "dlLoader/dlLoader.hpp"
#include "Consts/const.hpp"
#include "DesignPatterns/Factory.hpp"

extern "C" std::unique_ptr<RayTracer::I_Primitive> getPrimitive() {
    return std::make_unique<PrimPlane>();
}

PrimPlane::PrimPlane() {}

bool PrimPlane::hits(RayTracer::Ray ray, RayTracer::Point3D &intersection) {
    RayTracer::Vector3D normal = getRotatedNormal();

    float denom = normal.dot(ray.direction);
    if (std::abs(denom) > 1e-6) {
        RayTracer::Vector3D diff = position - ray.origin;
        float t = diff.dot(normal) / denom;
        if (t >= 0) {
            intersection = ray.origin + ray.direction * t;
            return true;
        }
    }
    return false;
}

RayTracer::Vector3D PrimPlane::getNormalAt(RayTracer::Point3D point) {
    (void)point;
    return getRotatedNormal();
}

RayTracer::Vector3D PrimPlane::getUV(RayTracer::Point3D point) {
    RayTracer::Vector3D local = point - position;

    local = getRotatedVector(local);

    return RayTracer::Vector3D(local.x, local.z, 0);
}

void PrimPlane::Init(std::unordered_map<std::string, std::any> &settings) {
    position = std::any_cast<RayTracer::Point3D>(settings["position"]);
    rotation = std::any_cast<RayTracer::Vector3D>(settings["rotation"]);
    radius = std::any_cast<float>(settings["radius"]);
    try {
        material = std::any_cast<std::shared_ptr<Mat>>(settings["material"]);
    } catch (const std::exception &e) {};
}

RayTracer::Vector3D PrimPlane::getRotatedNormal() const {
    RayTracer::Vector3D normal(0, 1, 0);

    normal = getRotatedVector(normal);

    return normal.normalize();
}

RayTracer::Vector3D PrimPlane::getRotatedVector(RayTracer::Vector3D vector)
const {
    RayTracer::Vector3D vec(vector.x, vector.y, vector.z);
    float rx = rotation.x * M_PI / 180.0f;
    float ry = rotation.y * M_PI / 180.0f;
    float rz = rotation.z * M_PI / 180.0f;

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
