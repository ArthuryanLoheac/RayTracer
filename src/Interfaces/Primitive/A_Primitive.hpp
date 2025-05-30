#pragma once
#include <memory>
#include <vector>
#include <string>

#include "Interfaces/Primitive/I_Primitive.hpp"

namespace RayTracer {
class A_Primitive : public I_Primitive {
 protected:
    std::vector<std::shared_ptr<I_Primitive>> childrens;
    std::shared_ptr<I_Material> material;
    Point3D position;
    Vector3D rotation;
    Point3D scale;

 public:
    virtual ~A_Primitive() = default;
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

    bool returnCollision(float A, float B, float C,
        Point3D &intersection, Ray &ray);

    class PrimitiveError : public std::exception {
     private:
        std::string message;

     public:
        explicit PrimitiveError(const std::string &message);
        const char *what() const noexcept override {
            return message.c_str();
        }
    };
};
}  // namespace RayTracer
