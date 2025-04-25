#pragma once
#include "3dDatas/Point3D.hpp"
#include "3dDatas/Ray.hpp"

namespace RayTracer {
class Sphere {
 public:
    Point3D center;
    double radius;
    Sphere() = default;
    Sphere(Point3D p, double r) : center(p), radius(r) {}
    bool hits(RayTracer::Ray ray);
};
}  // namespace RayTracer
