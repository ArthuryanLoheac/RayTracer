#pragma once
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Ray.hpp"
#include "Rectangle3D.hpp"

namespace RayTracer
{
class Camera {
 public:
    Point3D origin;
    Rectangle3D screen;

    Camera(); // Default constructor
    Ray ray(double u, double v);
};
} // namespace RayTracer