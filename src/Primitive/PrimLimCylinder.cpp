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
    RayTracer::Vector3D baseToPoint = point - position;

    float proj = baseToPoint.dot(rotation);

    const float height = this->height;

    if (proj <= 1e-4f)
        return -rotation;

    if (proj >= height - 1e-4f)
        return rotation;

    RayTracer::Point3D projected = position + rotation * proj;
    return (point - projected).normalize();
}

void PrimLimCylinder::Init
    (std::unordered_map<std::string, std::any> &settings) {
    rotation = std::any_cast<RayTracer::Vector3D>(settings["rotation"]);
    position = std::any_cast<RayTracer::Point3D>(settings["position"]);
    radius = std::any_cast<float>(settings["radius"]);
    material = std::any_cast<std::shared_ptr<Mat>>(settings["material"]);
    height = std::any_cast<float>(settings["height"]);
}

RayTracer::Vector3D PrimLimCylinder::getUV(RayTracer::Point3D point) {
    RayTracer::Vector3D local = point - position;

    float v = local.dot(rotation) / height;

    RayTracer::Vector3D axisX = rotation.orthogonal();
    RayTracer::Vector3D axisZ = rotation.cross(axisX);

    RayTracer::Vector3D radial = local - rotation * local.dot(rotation);

    float x = radial.dot(axisX);
    float z = radial.dot(axisZ);
    float theta = std::atan2(z, x);
    float u = (theta + M_PI) / (2 * M_PI);

    return RayTracer::Vector3D(u, v, 0);
}
