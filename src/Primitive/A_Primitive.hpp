#pragma once
#include <memory>
#include <vector>

#include "Primitive/I_Primitive.hpp"

namespace RayTracer {
class A_Primitive : public I_Primitive {
 protected:
    std::shared_ptr<I_Primitive> parent;
    std::vector<std::shared_ptr<I_Primitive>> childrens;
    std::shared_ptr<I_Material> material;
    Point3D position;
    Point3D rotation;
    Point3D scale;

 public:
    virtual ~A_Primitive() = default;
    virtual void Init() = 0;
    std::shared_ptr<I_Primitive> getParent() override;
    void setParent(std::shared_ptr<I_Primitive> parent) override;
    std::vector<std::shared_ptr<I_Primitive>> &getChildrens() override;
    void AddChildren(std::shared_ptr<I_Primitive> child) override;
    std::shared_ptr<I_Material> getMaterial() override;
    Point3D getPosition() override;
    Point3D getRotation() override;
    Point3D getScale() override;
};
}  // namespace RayTracer
