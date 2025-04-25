#pragma once
#include "Vector3D.hpp"
#include "Point3D.hpp"

namespace RayTracer
{
class Ray {
 public:
    RayTracer::Point3D origin;
    RayTracer::Vector3D direction;
    Ray() = default;
    Ray(RayTracer::Point3D _origin, RayTracer::Vector3D _direction);
    void normalized();
};
} // namespace RayTracer
