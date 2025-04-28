#pragma once
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
    virtual std::shared_ptr<I_Primitive> getParent() override;
    virtual void setParent(std::shared_ptr<I_Primitive> parent) override;
    virtual std::vector<std::shared_ptr<I_Primitive>> &getChildrens() override;
    virtual void AddChildren(std::shared_ptr<I_Primitive> child) override;
    virtual std::shared_ptr<I_Material> getMaterial() override;
    virtual Point3D getPosition() override;
    virtual Point3D getRotation() override;
    virtual Point3D getScale() override;
};
}  // namespace RayTracer