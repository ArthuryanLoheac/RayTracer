#pragma once
#include <memory>

#include "Interfaces/Primitive/I_Primitive.hpp"
#include "3dDatas/Point3D.hpp"

class hitDatas {
 public:
    hitDatas() {}
    float len;
    RayTracer::Point3D intersection;
    RayTracer::Point3D origin;
    RayTracer::Vector3D direction;
    std::shared_ptr<RayTracer::I_Primitive> obj;
};
