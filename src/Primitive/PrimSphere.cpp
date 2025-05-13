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

    return returnCollision(a, b, c, intersection, ray);
}

RayTracer::Vector3D PrimSphere::getNormalAt(RayTracer::Point3D point) {
    return (point - position).normalize();
}

RayTracer::Vector3D PrimSphere::getUV(RayTracer::Point3D point) {
    RayTracer::Vector3D vec = point - position;
    vec = vec.normalize();

    float theta = std::atan2(vec.x, vec.z);
    float phi = std::acos(vec.y);

    float u = 1.0f - (theta / (2.0f * M_PI) + 0.5f);
    float v = 1.0f - phi / M_PI;

    return RayTracer::Vector3D(u, v, 0);
}

void PrimSphere::Init() {
    static int i = 0;

    rotation = RayTracer::Vector3D(2, 0, 0);
    if (i == 0) {
        position = RayTracer::Point3D(0, -1, 5);
        radius = 1.f;
    } else {
        position = RayTracer::Point3D(0, .1f, 5);
        radius = 0.2f;
    }
    i++;

    try {
        material = dlLoader<Mat>::getLib("libs/mat_chess.so", "getMaterial");
    } catch (std::exception &e) {
        material = nullptr;
    }
}
