#include <memory>
#include <algorithm>
#include <cmath>
#include <string>

#include "Primitive/PrimCylinder.hpp"
#include "dlLoader/dlLoader.hpp"
#include "Consts/const.hpp"
#include "DesignPatterns/Factory.hpp"

extern "C" std::unique_ptr<RayTracer::I_Primitive> getPrimitive() {
    return std::make_unique<PrimCylinder>();
}

PrimCylinder::PrimCylinder() {
}

bool PrimCylinder::hits(RayTracer::Ray ray, RayTracer::Point3D &intersection) {
    RayTracer::Vector3D deltaP = ray.origin - position;
    RayTracer::Vector3D vPerp = ray.direction - rotation *
        ray.direction.dot(rotation);
    RayTracer::Vector3D deltaPPerp = deltaP - rotation * deltaP.dot(rotation);

    float A = vPerp.dot(vPerp);
    float B = 2.0f * vPerp.dot(deltaPPerp);
    float C = deltaPPerp.dot(deltaPPerp) - radius * radius;

    return returnCollision(A, B, C, intersection, ray);
}

RayTracer::Vector3D PrimCylinder::getNormalAt(RayTracer::Point3D point) {
    RayTracer::Point3D posUpdated = position;
    posUpdated.y = point.y;
    return (point - posUpdated).normalize();
}

void PrimCylinder::Init(std::unordered_map<std::string, std::any> &settings) {
    rotation = std::any_cast<RayTracer::Vector3D>(settings["rotation"]);
    position = std::any_cast<RayTracer::Point3D>(settings["position"]);
    radius = std::any_cast<float>(settings["radius"]);
    try {
        try {
        material = std::any_cast<std::shared_ptr<Mat>>(settings["material"]);
    } catch (const std::exception &e) {};
    } catch (const std::exception &e) {};
}

RayTracer::Vector3D PrimCylinder::getUV(RayTracer::Point3D point) {
    float theta = std::atan2(point.x, point.z);
    float raw_u = theta / (2 * M_PI);
    float u = 1 - (raw_u + 0.5);

    float v = point.y;

    return RayTracer::Vector3D(u, v, 0);
}
