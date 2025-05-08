#include <memory>
#include <algorithm>

#include "Primitive/PrimCylinder.hpp"
#include "dlLoader/dlLoader.hpp"
#include "Consts/const.hpp"

extern "C" std::unique_ptr<RayTracer::I_Primitive> getPrimitive() {
    return std::make_unique<PrimCylinder>();
}

PrimCylinder::PrimCylinder() {
    Init();
}

bool PrimCylinder::hits(RayTracer::Ray ray, RayTracer::Point3D &intersection) {
    RayTracer::Vector3D deltaP = ray.origin - position;
    RayTracer::Vector3D vPerp = ray.direction - va * ray.direction.dot(va);
    RayTracer::Vector3D deltaPPerp = deltaP - va * deltaP.dot(va);

    float A = vPerp.dot(vPerp);
    float B = 2.0f * vPerp.dot(deltaPPerp);
    float C = deltaPPerp.dot(deltaPPerp) - radius * radius;

    float d = B * B - 4.0f * A * C;

    float t1 = (-B - std::sqrt(d)) / (2 * A);
    float t2 = (-B + std::sqrt(d)) / (2 * A);
    float t = (t1 < t2) ? t1 : t2;
    if (t < 0)
        return false;
    intersection = ray.origin + ray.direction * t;
    if (d >= 0)
        return true;
    return false;
}

RayTracer::Vector3D PrimCylinder::getNormalAt(RayTracer::Point3D point) {
    RayTracer::Point3D posUpdated = position;
    posUpdated.y = point.y;
    return (point - posUpdated).normalize();
}

void PrimCylinder::Init() {
    static int i = 0;

    va = RayTracer::Vector3D(0, 1, 0);
    if (i == 0) {
        position = RayTracer::Point3D(0, -1, 5);
        radius = 0.1f;
    } else {
        position = RayTracer::Point3D(0, .1f, 5);
        radius = 0.2f;
    }
    i++;

    try {
        material = dlLoader<Mat>::getLib("libs/mat_flat.so", "getMaterial");
    } catch (std::exception &e) {
        material = nullptr;
    }
}
