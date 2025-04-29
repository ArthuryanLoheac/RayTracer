#pragma once
#include <memory>
#include <vector>

#include "3dDatas/Point3D.hpp"
#include "3dDatas/Ray.hpp"
#include "Material/I_Material.hpp"

namespace RayTracer {
class I_Primitive {
 public:
    virtual ~I_Primitive() = default;
    virtual void Init() = 0;

    virtual std::shared_ptr<I_Primitive> getParent() = 0;
    virtual void setParent(std::shared_ptr<I_Primitive> parent) = 0;
    virtual std::vector<std::shared_ptr<I_Primitive>> &getChildrens() = 0;
    virtual void AddChildren(std::shared_ptr<I_Primitive> child) = 0;

    virtual std::shared_ptr<I_Material> getMaterial() = 0;
    virtual Point3D getPosition() = 0;
    virtual Point3D getRotation() = 0;
    virtual Point3D getScale() = 0;

    virtual bool hits(RayTracer::Ray ray) = 0;
};
}  // namespace RayTracer

// extern "C" std::unique_ptr<I_Primitive> getPrimitive();
