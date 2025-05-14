#pragma once
#include "3dDatas/Point3D.hpp"
#include "3dDatas/Vector3D.hpp"
#include "3dDatas/Ray.hpp"
#include "3dDatas/Rectangle3D.hpp"
#include "3dDatas/Matrix4x4.hpp"  // Include for 4x4 matrix operations

namespace RayTracer {
class Camera {
 private:
    double aspect_ratio;
    int image_width;
    int image_height;
    double vfov;  // vertical field of view
    Point3D lookingAt;
    Matrix4x4 camera_to_world;  // 4x4 transformation matrix
 public:
    Point3D origin;
    Rectangle3D screen;

    Camera();  // Default constructor
    Ray ray(double u, double v);

    void rotate(double angleX, double angleY, double angleZ);
};
}  // namespace RayTracer
