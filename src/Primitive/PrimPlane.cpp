#include <memory>
#include <cmath>

#include "Primitive/PrimPlane.hpp"
#include "dlLoader/dlLoader.hpp"
#include "Consts/const.hpp"
#include "DesignPatterns/Factory.hpp"

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

RayTracer::Vector3D PrimPlane::getUV(RayTracer::Point3D point) {
    float u = point.x;
    float v = point.z;
    return RayTracer::Vector3D(u, v, 0);
}

void PrimPlane::Init() {
    position = RayTracer::Point3D(0, -2, 5);
    rotation = RayTracer::Vector3D(0, 1, 0);
    radius = 1.f;

    try {
        material = Factory<Mat>::i().create("perlin");
    } catch (std::exception &e) {
        material = nullptr;
    }
}
