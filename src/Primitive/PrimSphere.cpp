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

    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return false;

    double t1 = (-b - std::sqrt(discriminant)) / (2.0 * a);
    double t2 = (-b + std::sqrt(discriminant)) / (2.0 * a);
    double t = (t1 < 0) ?
        (t2 < 0 ? -1 : t2) :
        (t2 < 0 ? t1 : std::min(t1, t2));

    intersection = ray.origin + ray.direction * t;
    if (t < 0)
        return false;
    return true;
}

RayTracer::Vector3D PrimSphere::getNormalAt(RayTracer::Point3D point) {
    return (point - position).normalize();
}

void PrimSphere::Init() {
    static int i = 0;

    if (i == 0) {
        position = RayTracer::Point3D(0, -1, 5);
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
