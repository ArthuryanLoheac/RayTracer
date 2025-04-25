#pragma once
#include "Point3D.hpp"
#include "Ray.hpp"

namespace RayTracer
{
class Sphere {
 public:
    Point3D center;
    double radius;
    Sphere() = default;
    Sphere(Point3D p, double r) : center(p), radius(r) {};
    bool hits(RayTracer::Ray ray);
};
} // namespace RayTracer
