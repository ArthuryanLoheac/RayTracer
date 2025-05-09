#include <memory>
#include <algorithm>

#include "Primitive/PrimSphere.hpp"
#include "dlLoader/dlLoader.hpp"
#include "Consts/const.hpp"

extern "C" std::unique_ptr<RayTracer::I_Primitive> getPrimitive() {
    return std::make_unique<PrimSphere>();
}

PrimSphere::PrimSphere() {
    Init();
}

bool PrimSphere::hits(RayTracer::Ray ray, RayTracer::Point3D &intersection) {
    RayTracer::Vector3D oc = ray.origin - position;

    // Quadratic coefficients
    double a = ray.direction.dot(ray.direction);
    double b = 2.0 * oc.dot(ray.direction);
    double c = oc.dot(oc) - radius * radius;

    double d = b * b - 4 * a * c;
    return returnCollision(a, b, c, intersection, ray);
}

RayTracer::Vector3D PrimSphere::getNormalAt(RayTracer::Point3D point) {
    return (point - position).normalize();
}

void PrimSphere::Init() {
    static int i = 0;

    if (i == 0) {
        position = RayTracer::Point3D(0, -4, 5);
        radius = 1.f;
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
