#include <memory>

#include "Primitive/PrimSphere.hpp"
#include "dlLoader/dlLoader.hpp"
#include "Consts/const.hpp"

extern "C" std::unique_ptr<RayTracer::I_Primitive> getPrimitive() {
    return std::make_unique<PrimSphere>();
}

bool PrimSphere::hits(RayTracer::Ray ray) {
    RayTracer::Vector3D oc = ray.origin - center;

    // Quadratic coefficients
    double a = ray.direction.dot(ray.direction);
    double b = 2.0 * oc.dot(ray.direction);
    double c = oc.dot(oc) - radius * radius;

    // Discriminant
    double discriminant = b * b - 4 * a * c;

    return discriminant >= 0;
}

void PrimSphere::Init() {
    center = RayTracer::Point3D(0.02f, 0.17f, -1);
    radius = 0.1f;

    try {
        material = dlLoader<Mat>::getLib("libs/mat_flat.so", "getMaterial");
    } catch (std::exception &e) {
        material = nullptr;
    }
}