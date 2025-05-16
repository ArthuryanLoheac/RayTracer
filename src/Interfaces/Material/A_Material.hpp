#pragma once
#include "Interfaces/Material/I_Material.hpp"

namespace RayTracer {
class A_Material : public I_Material
{
 private:
    sf::Image img;
    bool hasNormal;
 public:
    virtual bool isReflective() const override;
    virtual RayTracer::Vector3D getNormalAt(float u, float v) override;
    virtual void setNormal(std::string path) override;

    Vector3D rotatedNormal(const Vector3D &normal, Vector3D &normalMap, const Vector3D &tangent,
      const Vector3D &bitangent) const override;

    class MaterialError : public std::exception
    {
     public:
        explicit MaterialError(const std::string &message) : msg_(message) {}
        virtual const char *what() const noexcept override
        {
            return msg_.c_str();
        }

     private:
        std::string msg_;
    };
};
}