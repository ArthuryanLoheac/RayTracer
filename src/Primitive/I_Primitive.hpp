#pragma once
#include <memory>

#include "3dDatas/Point3D.hpp"
#include "Material/I_Material.hpp"

namespace RayTracer {
class I_Primitive {
 public:
    virtual ~I_Primitive() = default;
    virtual void Init() = 0;
    virtual std::unique_ptr<I_Primitive> getParent() = 0;
    virtual void setParent(std::unique_ptr<I_Primitive> parent) = 0;
    virtual I_Material getMaterial() = 0;
    virtual Point3D getPosition() = 0;
    virtual Point3D getRotation() = 0;
    virtual Point3D getScale() = 0;
};
}  // namespace RayTracer

// extern "C" std::unique_ptr<I_Primitive> getPrimitive();