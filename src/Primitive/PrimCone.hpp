#pragma once

#include "Interfaces/Primitive/A_Primitive.hpp"
#include "3dDatas/Point3D.hpp"
#include "3dDatas/Vector3D.hpp"
#include "3dDatas/Ray.hpp"

class PrimCone : public RayTracer::A_Primitive {
 public:
    double angle;
    PrimCone();
    bool hits(RayTracer::Ray ray, RayTracer::Point3D &intersection) override;
    RayTracer::Vector3D getNormalAt(RayTracer::Point3D point) override;
    RayTracer::Vector3D getUV(RayTracer::Point3D point) override;
    void Init(std::unordered_map<std::string, std::any> &settings) override;
};
