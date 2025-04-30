#pragma once
#include <memory>
#include <vector>
#include <string>

#include "Interfaces/Light/I_Light.hpp"

namespace RayTracer {
class A_Lights : public I_Light {
 protected:
    std::shared_ptr<I_Primitive> parent;
    std::vector<std::shared_ptr<I_Primitive>> childrens;
    std::shared_ptr<I_Material> material;
    Point3D position;
    Point3D rotation;
    Point3D scale;

    float angle;
    float intensity;

 public:
    virtual ~A_Lights() = default;
    virtual void Init() override = 0;
    std::shared_ptr<I_Primitive> getParent() override;
    void setParent(std::shared_ptr<I_Primitive> parent) override;
    std::vector<std::shared_ptr<I_Primitive>> &getChildrens() override;
    void AddChildren(std::shared_ptr<I_Primitive> child) override;
    std::shared_ptr<I_Material> getMaterial() override;
    void setMaterial(std::shared_ptr<I_Material> material) override;
    Point3D getPosition() override;
    Point3D getRotation() override;
    Point3D getScale() override;

    float getLuminescence(float distance, float angle) = 0;
    float getIntensity() override;
    float getAngle() override;

    class LightError : public std::exception {
     private:
        std::string message;

     public:
        explicit LightError(const std::string &message);
        const char *what() const noexcept override {
            return message.c_str();
        }
    };
};
}  // namespace RayTracer
