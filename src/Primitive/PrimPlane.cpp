/*
** EPITECH PROJECT, 2025
** RayTracer
** File description:
** PrimPlane
*/

#include <memory>

#include "Primitive/PrimPlane.hpp"
#include "dlLoader/dlLoader.hpp"
#include "Consts/const.hpp"

extern "C" std::unique_ptr<RayTracer::I_Primitive> getPrimitive() {
    return std::make_unique<PrimPlane>();
}

PrimPlane::PrimPlane() {
    Init();
}

bool PrimPlane::hits(RayTracer::Ray ray, RayTracer::Point3D &intersection) {
    double denom = rotation.dot(ray.direction);
    if (std::abs(denom) > 1e-6) {
        RayTracer::Vector3D p0l0 = position - ray.origin;
        double t = p0l0.dot(rotation) / denom;
        if (t >= 0) {
            intersection = ray.origin + ray.direction * t;
            return true;
        }
    }
    return false;
}

RayTracer::Vector3D PrimPlane::getNormalAt(RayTracer::Point3D point) {
    (void)point;
    return rotation;
}

void PrimPlane::Init() {
    position = RayTracer::Point3D(0, -2, 5);
    rotation = RayTracer::Vector3D(0, 1, 0);
    radius = 10.f;

    try {
        material = dlLoader<Mat>::getLib("libs/mat_flat.so", "getMaterial");
    } catch (std::exception &e) {
        material = nullptr;
    }
}
