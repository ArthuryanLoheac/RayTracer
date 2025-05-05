#pragma once
#include <memory>
#include <vector>
#include <string>

#include "Interfaces/Light/I_Light.hpp"

namespace RayTracer {
class A_Lights : public I_Light {
 protected:
    std::vector<std::shared_ptr<I_Primitive>> childrens;
    std::shared_ptr<I_Material> material;
    Point3D position;
    Point3D rotation;
    Point3D scale;

    float angle;
    float intensity;

 public:
    virtual ~A_Lights() = default;
    std::vector<std::shared_ptr<I_Primitive>> &getChildrens() override;
    std::shared_ptr<I_Primitive> &AddChildren(
       std::shared_ptr<I_Primitive> child) override;
    std::shared_ptr<I_Material> getMaterial() override;
    void setMaterial(std::shared_ptr<I_Material> material) override;
    Point3D getPosition() override;
    void setPosition(Point3D pos) override;
    Point3D getRotation() override;
    void setRotation(Point3D rot) override;
    Point3D getScale() override;
    void setScale(Point3D scale) override;

    float getLuminescence(float angle, float distance) = 0;
    float getIntensity() override;
    float getAngle() override;
    Vector3D getNormalAt(Point3D point) override;

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
