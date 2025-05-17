#pragma once
#include <any>
#include <string>
#include <unordered_map>

#include "3dDatas/Point3D.hpp"
#include "3dDatas/Vector3D.hpp"
#include "3dDatas/Ray.hpp"
#include "3dDatas/Rectangle3D.hpp"
#include "3dDatas/Matrix4x4.hpp"

namespace RayTracer {
class Camera {
 private:
    double aspect_ratio;
    double vfov;  // vertical field of view
    Point3D lookingAt;
    Matrix4x4 camera_to_world;
 public:
    static Camera &i() {
        static Camera instance;
        return instance;
    }
    Point3D origin;
    Rectangle3D screen;
    Vector3D rotation;
    int image_width;
    int image_height;

    Camera();
    Ray ray(double u, double v);

    void Init(std::unordered_map<std::string, std::any> &settings);
    void rotate(double angleX, double angleY, double angleZ);
};
}  // namespace RayTracer
