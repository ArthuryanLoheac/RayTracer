#include <memory>
#include <algorithm>

#include "Primitive/PrimCone.hpp"
#include "dlLoader/dlLoader.hpp"
#include "Consts/const.hpp"

extern "C" std::unique_ptr<RayTracer::I_Primitive> getPrimitive() {
    return std::make_unique<PrimCone>();
}

PrimCone::PrimCone() {
    Init();
}

bool PrimCone::hits(RayTracer::Ray ray, RayTracer::Point3D &intersection) {
    RayTracer::Vector3D deltaP = ray.origin - position;
    float cos2 = cos(angle) * cos(angle);
    float sin2 = sin(angle) * sin(angle);

    float A = cos2 * std::pow(
            ((ray.direction - va * va.dot(ray.direction)).length()), 2)
            - sin2 * pow(va.dot(ray.direction), 2);
    float B = 2.0f * cos2 * (ray.direction - va * va.dot(ray.direction))
                         .dot(deltaP - va * va.dot(deltaP))
         - 2.0f * sin2 * va.dot(ray.direction) * va.dot(deltaP);
    float C = cos2 * std::pow((deltaP - va * va.dot(deltaP)).length(), 2)
            - sin2 * std::pow(va.dot(deltaP), 2);

    return returnCollision(A, B, C, intersection, ray);
}

RayTracer::Vector3D PrimCone::getNormalAt(RayTracer::Point3D point) {
    RayTracer::Point3D posUpdated = position;
    posUpdated.y = point.y;
    return (point - posUpdated).normalize();
}

void PrimCone::Init() {
    static int i = 0;

    va = RayTracer::Vector3D(0, 1, 0);
    if (i == 0) {
        position = RayTracer::Point3D(0, -1, 5);
        angle = 10;
    } else {
        position = RayTracer::Point3D(0, .1f, 5);
        angle = 20;
    }
    i++;

    try {
        material = dlLoader<Mat>::getLib("libs/mat_flat.so", "getMaterial");
    } catch (std::exception &e) {
        material = nullptr;
    }
}
