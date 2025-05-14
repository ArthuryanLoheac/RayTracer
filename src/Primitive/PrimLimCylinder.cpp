#include <memory>
#include <algorithm>
#include <cmath>
#include <utility>
#include <limits>

#include "Primitive/PrimLimCylinder.hpp"
#include "dlLoader/dlLoader.hpp"
#include "Consts/const.hpp"
#include "DesignPatterns/Factory.hpp"

extern "C" std::unique_ptr<RayTracer::I_Primitive> getPrimitive() {
    return std::make_unique<PrimLimCylinder>();
}

PrimLimCylinder::PrimLimCylinder() {
    Init();
}

static bool returnCollisionLimCyl
    (float A, float B, float C, float &t1, float &t2) {
    float discriminant = B * B - 4.0f * A * C;

    if (discriminant < 0.0f)
        return false;

    float sqrtD = std::sqrt(discriminant);
    float q = (B < 0) ? (-B - sqrtD) / 2.0f : (-B + sqrtD) / 2.0f;

    if (A == 0.0f)
        return false;

    t1 = q / A;
    t2 = C / q;

    if (t1 > t2) std::swap(t1, t2);

    return true;
}

bool PrimLimCylinder::hits
    (RayTracer::Ray ray, RayTracer::Point3D &intersection) {
    RayTracer::Vector3D deltaP = ray.origin - position;
    RayTracer::Vector3D v = ray.direction;
    RayTracer::Vector3D d = rotation;

    RayTracer::Vector3D vPerp = v - d * v.dot(d);
    RayTracer::Vector3D deltaPPerp = deltaP - d * deltaP.dot(d);

    float A = vPerp.dot(vPerp);
    float B = 2.0f * vPerp.dot(deltaPPerp);
    float C = deltaPPerp.dot(deltaPPerp) - radius * radius;

    float t1, t2;
    bool hit = false;
    float t = std::numeric_limits<float>::max();

    if (returnCollisionLimCyl(A, B, C, t1, t2)) {
        for (float ti : {t1, t2}) {
            if (ti < 0) continue;
            RayTracer::Point3D p = ray.origin + ray.direction * ti;
            float proj = (p - position).dot(d);
            if (proj >= 0 && proj <= height) {
                if (ti < t) {
                    t = ti;
                    hit = true;
                }
            }
        }
    }
    for (int cap = 0; cap < 2; ++cap) {
        float capDist = (cap == 0) ? 0 : height;
        RayTracer::Point3D capCenter = position + d * capDist;
        float denom = ray.direction.dot(d);
        if (std::abs(denom) > 1e-6f) {
            float tCap = ((capCenter - ray.origin).dot(d)) / denom;
            if (tCap > 0 && tCap < t) {
                RayTracer::Point3D p = ray.origin + ray.direction * tCap;
                if ((p - capCenter).lengthSquared() <= radius * radius) {
                    t = tCap;
                    hit = true;
                }
            }
        }
    }

    if (hit) {
        intersection = ray.origin + ray.direction * t;
        return true;
    }

    return false;
}

RayTracer::Vector3D PrimLimCylinder::getNormalAt(RayTracer::Point3D point) {
    RayTracer::Point3D posUpdated = position;
    posUpdated.y = point.y;
    return (point - posUpdated).normalize();
}

void PrimLimCylinder::Init() {
    rotation = RayTracer::Vector3D(0, 1, 0);
    position = RayTracer::Point3D(0, -2, 4);
    height = 1;
    radius = 1.f;

    try {
        material = Factory<Mat>::i().create("perlin");
    } catch (std::exception &e) {
        material = nullptr;
    }
}

RayTracer::Vector3D PrimLimCylinder::getUV(RayTracer::Point3D point) {
    float theta = std::atan2(point.x, point.z);
    float raw_u = theta / (2 * M_PI);
    float u = 1 - (raw_u + 0.5);

    float v = point.y;

    return RayTracer::Vector3D(u, v, 0);
}
