#pragma once
#include <memory>

#include "Interfaces/Primitive/I_Primitive.hpp"
#include "3dDatas/Point3D.hpp"

class hitDatas {
 public:
    hitDatas() {};
    float len;
    RayTracer::Point3D intersection;
    std::shared_ptr<RayTracer::I_Primitive> obj;
};
