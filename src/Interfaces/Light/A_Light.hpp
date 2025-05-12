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
    Vector3D rotation;
    Point3D scale;
    sf::Color color;

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
    Vector3D getRotation() override;
    void setRotation(Vector3D rot) override;
    Point3D getScale() override;
    void setScale(Point3D scale) override;

    float getLuminescence(RayTracer::Point3D intersection,
        std::shared_ptr<I_Light> Light, std::shared_ptr<I_Primitive> obj,
         std::shared_ptr<I_Primitive> head) = 0;
    float getIntensity() override;
    float getAngle() override;
    Vector3D getNormalAt(Point3D point) override;
    bool hits(RayTracer::Ray ray, Point3D &intersection) override;
    sf::Color getColor() override;

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
