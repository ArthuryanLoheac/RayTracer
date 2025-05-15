#include "Primitive/PrimPlane.hpp"
#include <cmath>
#include <iostream>
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

    float rx = -rotation.x * M_PI / 180.0f;
    float ry = -rotation.y * M_PI / 180.0f;
    float rz = -rotation.z * M_PI / 180.0f;

    // Rotation Z
    local = RayTracer::Vector3D(
        local.x * cos(rz) - local.y * sin(rz),
        local.x * sin(rz) + local.y * cos(rz),
        local.z
    );

    // Rotation Y
    local = RayTracer::Vector3D(
        local.x * cos(ry) + local.z * sin(ry),
        local.y,
        -local.x * sin(ry) + local.z * cos(ry)
    );

    // Rotation X
    local = RayTracer::Vector3D(
        local.x,
        local.y * cos(rx) - local.z * sin(rx),
        local.y * sin(rx) + local.z * cos(rx)
    );

    return RayTracer::Vector3D(local.x, local.y, 0);
}

void PrimPlane::Init(std::unordered_map<std::string, std::any> &settings) {
    position = std::any_cast<RayTracer::Point3D>(settings["position"]);
    rotation = std::any_cast<RayTracer::Vector3D>(settings["rotation"]);
    radius = std::any_cast<float>(settings["radius"]);
    material = std::any_cast<std::shared_ptr<RayTracer::I_Material>>(settings["material"]);
}

/// Fonction utilitaire : retourne la normale après rotation
RayTracer::Vector3D PrimPlane::getRotatedNormal() const {
    RayTracer::Vector3D normal(0, 1, 0);

    float rx = rotation.x * M_PI / 180.0f;
    float ry = rotation.y * M_PI / 180.0f;
    float rz = rotation.z * M_PI / 180.0f;

    // Axe X
    normal = RayTracer::Vector3D(
        normal.x,
        normal.y * cos(rx) - normal.z * sin(rx),
        normal.y * sin(rx) + normal.z * cos(rx)
    );

    // Axe Y
    normal = RayTracer::Vector3D(
        normal.x * cos(ry) + normal.z * sin(ry),
        normal.y,
        -normal.x * sin(ry) + normal.z * cos(ry)
    );

    // Axe Z
    normal = RayTracer::Vector3D(
        normal.x * cos(rz) - normal.y * sin(rz),
        normal.x * sin(rz) + normal.y * cos(rz),
        normal.z
    );

    return normal.normalize();
}
