#include <memory>
#include <cmath>
#include <string>

#include "Primitive/PrimPlane.hpp"
#include "dlLoader/dlLoader.hpp"
#include "Consts/const.hpp"
#include "DesignPatterns/Factory.hpp"

extern "C" std::unique_ptr<RayTracer::I_Primitive> getPrimitive() {
    return std::make_unique<PrimPlane>();
}

PrimPlane::PrimPlane() {
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

void PrimPlane::Init(std::unordered_map<std::string, std::any> &settings) {
    position = std::any_cast<RayTracer::Point3D>(settings["position"]);
    rotation = std::any_cast<RayTracer::Vector3D>(settings["rotation"]);
    radius = std::any_cast<float>(settings["radius"]);
    material = std::any_cast<std::shared_ptr<Mat>>(settings["material"]);
}
