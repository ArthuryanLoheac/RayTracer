#include <memory>
#include <algorithm>
#include <string>
#include <utility>
#include <limits>

#include "Primitive/PrimLimCone.hpp"
#include "dlLoader/dlLoader.hpp"
#include "Consts/const.hpp"
#include "DesignPatterns/Factory.hpp"
#include "Interfaces/Material/I_Material.hpp"

extern "C" std::unique_ptr<RayTracer::I_Primitive> getPrimitive() {
    return std::make_unique<PrimLimCone>();
}

PrimLimCone::PrimLimCone() {
}

static bool solveQuadraticLimCone
    (float A, float B, float C, float &t0, float &t1) {
    float discr = B * B - 4 * A * C;
    if (discr < 0.0f)
        return false;
    float sqrtDiscr = std::sqrt(discr);
    float q = (B < 0) ? -0.5f * (B - sqrtDiscr)
                      : -0.5f * (B + sqrtDiscr);
    t0 = q / A;
    t1 = C / q;
    if (t0 > t1)
        std::swap(t0, t1);
    return true;
}

bool PrimLimCone::hits(RayTracer::Ray ray, RayTracer::Point3D &intersection) {
    RayTracer::Vector3D va = rotation.normalized();
    RayTracer::Vector3D deltaP = ray.origin - position;
    float cos2 = std::cos(angle) * std::cos(angle);
    float sin2 = std::sin(angle) * std::sin(angle);
    float dv = va.dot(ray.direction);
    float dpv = va.dot(deltaP);
    RayTracer::Vector3D d_proj = ray.direction - va * dv;
    RayTracer::Vector3D dp_proj = deltaP - va * dpv;
    float A = cos2 * d_proj.dot(d_proj) - sin2 * dv * dv;
    float B = 2 * cos2 * d_proj.dot(dp_proj) - 2 * sin2 * dv * dpv;
    float C = cos2 * dp_proj.dot(dp_proj) - sin2 * dpv * dpv;
    float t0, t1;
    bool found = false;
    float tFinal = std::numeric_limits<float>::max();

    if (solveQuadraticLimCone(A, B, C, t0, t1)) {
        for (float t : {t0, t1}) {
            if (t < EPSILON) continue;
            RayTracer::Point3D hitPoint = ray.origin + ray.direction * t;
            float proj = (hitPoint - position).dot(va);

            if (proj >= 0 && proj <= height) {
                if (t < tFinal) {
                    tFinal = t;
                    intersection = hitPoint;
                    found = true;
                }
            }
        }
    }
    RayTracer::Point3D baseCenter = position + va * height;
    float radius = height * std::tan(angle);
    float denom = ray.direction.dot(va);
    if (std::abs(denom) > EPSILON) {
        float tCap = (baseCenter - ray.origin).dot(va) / denom;
        if (tCap > EPSILON) {
            RayTracer::Point3D hitPoint = ray.origin + ray.direction * tCap;
            RayTracer::Vector3D toCenter = hitPoint - baseCenter;
            if (toCenter.lengthSquared() <= radius * radius) {
                if (tCap < tFinal) {
                    tFinal = tCap;
                    intersection = hitPoint;
                    found = true;
                }
            }
        }
    }
    return found;
}

RayTracer::Vector3D PrimLimCone::getNormalAt(RayTracer::Point3D point) {
    RayTracer::Vector3D va = rotation.normalized();
    RayTracer::Point3D baseCenter = position + va * height;
    float radius = height * std::tan(angle);

    RayTracer::Vector3D toBase = point - baseCenter;
    if (std::abs((point - baseCenter).dot(va)) < EPSILON &&
        toBase.lengthSquared() <= radius * radius) {
        return va;
    }
    RayTracer::Vector3D pointToBase = point - position;
    RayTracer::Vector3D projection = va * pointToBase.dot(va);
    RayTracer::Vector3D radial = pointToBase - projection;
    RayTracer::Vector3D normal =
        radial - va * radial.length() / std::tan(angle);
    normal.normalize();
    return normal;
}


void PrimLimCone::Init(std::unordered_map<std::string, std::any> &settings) {
    try {
        rotation = std::any_cast<RayTracer::Vector3D>(settings["rotation"]);
        position = std::any_cast<RayTracer::Point3D>(settings["position"]);
        angle = std::any_cast<float>(settings["angle"]);
        height = std::any_cast<float>(settings["height"]);
        material = std::any_cast<std::shared_ptr<Mat>>(settings["material"]);
    } catch (const std::exception &e) {}
}

RayTracer::Vector3D PrimLimCone::getUV(RayTracer::Point3D point) {
    RayTracer::Vector3D va = rotation.normalized();
    RayTracer::Point3D baseCenter = position + va * height;
    float radius = height * std::tan(angle);

    RayTracer::Vector3D toBase = point - baseCenter;
    if (std::abs((point - baseCenter).dot(va)) < EPSILON &&
        toBase.lengthSquared() <= radius * radius) {
        float u = 0.5f + (toBase.x / radius) * 0.5f;
        float v = 0.5f + (toBase.z / radius) * 0.5f;
        return RayTracer::Vector3D(u, v, 0);
    }
    RayTracer::Vector3D pointToAxis = point - position;
    float theta = std::atan2(pointToAxis.x, pointToAxis.z);
    float u = (theta / (2.0f * M_PI)) + 0.5f;
    float v = pointToAxis.dot(va) / height;
    return RayTracer::Vector3D(u, v, 0);
}
