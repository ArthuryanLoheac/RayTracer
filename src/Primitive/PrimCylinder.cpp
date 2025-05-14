#include <memory>
#include <algorithm>
#include <cmath>

#include "Primitive/PrimCylinder.hpp"
#include "dlLoader/dlLoader.hpp"
#include "Consts/const.hpp"
#include "DesignPatterns/Factory.hpp"

extern "C" std::unique_ptr<RayTracer::I_Primitive> getPrimitive() {
    return std::make_unique<PrimCylinder>();
}

PrimCylinder::PrimCylinder() {
    Init();
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

void PrimCylinder::Init() {
    static int i = 0;

    rotation = RayTracer::Vector3D(0, 1, 0);
    if (i == 0) {
        position = RayTracer::Point3D(0, -1, 5);
        radius = 1.f;
    } else {
        position = RayTracer::Point3D(0, .1f, 5);
        radius = 0.2f;
    }
    i++;

    try {
        material = Factory<Mat>::i().create("chess");
    } catch (std::exception &e) {
        material = nullptr;
    }
}

RayTracer::Vector3D PrimCylinder::getUV(RayTracer::Point3D point) {
    float theta = std::atan2(point.x, point.z);
    float raw_u = theta / (2 * M_PI);
    float u = 1 - (raw_u + 0.5);

    float v = point.y;

    return RayTracer::Vector3D(u, v, 0);
}
