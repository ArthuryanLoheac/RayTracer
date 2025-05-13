#pragma once
#include "3dDatas/Point3D.hpp"
#include "3dDatas/Vector3D.hpp"
#include "3dDatas/Ray.hpp"
#include "3dDatas/Rectangle3D.hpp"

namespace RayTracer {
class Camera {
 private:
    double aspect_ratio;
    int image_width;
    int image_height;
    double vfov;  // vertical field of view
    Point3D lookingAt;
 public:
    Point3D origin;
    Rectangle3D screen;

    Camera();  // Default constructor
    Ray ray(double u, double v);
};
}  // namespace RayTracer
