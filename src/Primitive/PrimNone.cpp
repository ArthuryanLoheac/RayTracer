#include <memory>
#include <algorithm>
#include <string>
#include <unordered_map>

#include "Primitive/PrimNone.hpp"
#include "dlLoader/dlLoader.hpp"
#include "Consts/const.hpp"

extern "C" std::unique_ptr<RayTracer::I_Primitive> getPrimitive() {
    return std::make_unique<PrimNone>();
}

PrimNone::PrimNone() {
    std::unordered_map<std::string, std::any> settings;
    Init(settings);
}

bool PrimNone::hits(RayTracer::Ray ray, RayTracer::Point3D &intersection) {
    (void)ray;
    (void)intersection;
    return false;
}

RayTracer::Vector3D PrimNone::getNormalAt(RayTracer::Point3D point) {
    (void)point;
    return RayTracer::Vector3D(0, 0, 0);
}

void PrimNone::Init(std::unordered_map<std::string, std::any> &settings) {
    (void)settings;
    position = RayTracer::Point3D(0, 0, 0);
    radius = 0.f;
    material = nullptr;
}

RayTracer::Vector3D PrimNone::getUV(RayTracer::Point3D point) {
    (void)point;
    return RayTracer::Vector3D(0, 0, 0);
}
