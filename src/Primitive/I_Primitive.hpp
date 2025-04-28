#pragma once
#include <memory>

#include "3dDatas/Point3D.hpp"
#include "Material/I_Material.hpp"

namespace RayTracer {
class I_Primitive {
 public:
    I_Primitive() = default;
    virtual void Init() = 0;
    virtual std::unique_ptr<I_Primitive> getParent() = 0;
    virtual void setParent(std::unique_ptr<I_Primitive> parent) = 0;
    virtual I_Material getMaterial() = 0;
    virtual void setMaterial(I_Material material) = 0;
    virtual Point3D getPosition() = 0;
    virtual void setPosition(Point3D position) = 0;
    virtual Point3D getRotation() = 0;
    virtual void setRotation(Point3D rotation) = 0;
    virtual Point3D getScale() = 0;
    virtual void setScale(Point3D scale) = 0;
};
}  // namespace RayTracer

// extern "C" std::unique_ptr<I_Primitive> getPrimitive();