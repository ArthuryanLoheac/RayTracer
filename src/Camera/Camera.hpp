#pragma once
#include "3dDatas/Point3D.hpp"
#include "3dDatas/Vector3D.hpp"
#include "3dDatas/Ray.hpp"
#include "3dDatas/Rectangle3D.hpp"

namespace RayTracer {
class Camera {
 public:
    Point3D origin;
    Rectangle3D screen;

    Camera();  // Default constructor
    Ray ray(double u, double v);
};
}  // namespace RayTracer
