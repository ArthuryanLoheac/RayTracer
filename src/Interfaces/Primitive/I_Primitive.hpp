#pragma once
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

#include "3dDatas/Point3D.hpp"
#include "3dDatas/Ray.hpp"
#include "Interfaces/Material/I_Material.hpp"

namespace RayTracer {
class I_Primitive {
 public:
    virtual ~I_Primitive() = default;
    virtual void Init(std::unordered_map<std::string, std::any> &settings) = 0;

    virtual std::vector<std::shared_ptr<I_Primitive>> &getChildrens() = 0;
    virtual Vector3D getNormalAt(Point3D point) = 0;
    virtual std::shared_ptr<I_Primitive> &AddChildren(
        std::shared_ptr<I_Primitive> child) = 0;

    virtual std::shared_ptr<I_Material> getMaterial() = 0;
    virtual void setMaterial(std::shared_ptr<I_Material> material) = 0;
    virtual Point3D getPosition() = 0;
    virtual void setPosition(Point3D pos) = 0;
    virtual Vector3D getRotation() = 0;
    virtual void setRotation(Vector3D rot) = 0;
    virtual Point3D getScale() = 0;
    virtual void setScale(Point3D scale) = 0;

    virtual bool hits(RayTracer::Ray ray, RayTracer::Point3D &intersection) = 0;
    virtual RayTracer::Vector3D getUV(RayTracer::Point3D point) = 0;
};
}  // namespace RayTracer

// extern "C" std::unique_ptr<I_Primitive> getPrimitive();
