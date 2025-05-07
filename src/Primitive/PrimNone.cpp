#include <memory>
#include <algorithm>

#include "Primitive/PrimNone.hpp"
#include "dlLoader/dlLoader.hpp"
#include "Consts/const.hpp"

extern "C" std::unique_ptr<RayTracer::I_Primitive> getPrimitive() {
    return std::make_unique<PrimNone>();
}

PrimNone::PrimNone() {
    Init();
}

bool PrimNone::hits(RayTracer::Ray ray, RayTracer::Point3D &intersection) {
    (void)ray;
    (void)intersection;
    return false;
}

RayTracer::Vector3D PrimNone::getNormalAt(RayTracer::Point3D point) {
    (void)point;
    return RayTracer::Vector3D(0,0,0);
}

void PrimNone::Init() {
    position = RayTracer::Point3D(0, 0, 0);
    radius = 0.f;
    material = nullptr;
}
