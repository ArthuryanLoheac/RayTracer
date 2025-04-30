#pragma once

#include "Interfaces/Primitive/A_Primitive.hpp"
#include "3dDatas/Point3D.hpp"
#include "3dDatas/Vector3D.hpp"
#include "3dDatas/Ray.hpp"

class PrimSphere : public RayTracer::A_Primitive {
 public:
    double radius;
    PrimSphere();
    bool hits(RayTracer::Ray ray) override;
    void Init() override;
};
