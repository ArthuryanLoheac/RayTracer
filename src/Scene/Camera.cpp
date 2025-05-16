#include <iostream>
#include <cmath>
#include <unordered_map>
#include <any>
#include <string>

#include "Scene/Camera.hpp"
#include "Consts/const.hpp"

// ATENTION Camera position depends on  orientation

namespace RayTracer {
static double degrees_to_radians(double degrees) {
    return degrees * M_PI / 180.0;
}

Camera::Camera() {
}

Ray Camera::ray(double u, double v) {
    Point3D p = screen.pointAt(u, v);
    Point3D origin_world = camera_to_world.transformPoint(origin);
    Point3D p_world = camera_to_world.transformPoint(p);
    Vector3D ray_direction = (p_world - origin_world).normalized();

    return Ray(origin_world, ray_direction);
}

void Camera::Init(std::unordered_map<std::string, std::any> &settings) {
    image_width = std::any_cast<int>(settings["width"]);
    image_height = std::any_cast<int>(settings["height"]);
    vfov = std::any_cast<double>(settings["fov"]);
    origin = std::any_cast<Point3D>(settings["position"]);
    rotation = std::any_cast<Vector3D>(settings["rotation"]);
    aspect_ratio = static_cast<double>(image_width) /
        static_cast<double>(image_height);
    lookingAt = origin + Point3D(0, 0, 1);
    camera_to_world = Matrix4x4();

    auto focal_length = Vector3D(origin - lookingAt).length();
    auto theta = degrees_to_radians(vfov);
    auto h = std::tan(theta/2);
    auto viewport_height = 2 * h * focal_length;
    auto viewport_width = viewport_height *
        (static_cast<double>(image_width)/image_height);
    rotate(rotation.x, rotation.y, rotation.z);
    screen = Rectangle3D(
        Point3D(origin.x + -viewport_width / 2,
            origin.y +  viewport_height / 2,
            origin.z +  focal_length),
        Vector3D(1, 0, 0).normalized() * viewport_width,
        Vector3D(0, -1, 0).normalized() * viewport_height);
}

void Camera::rotate(double angleX, double angleY, double angleZ) {
    Matrix4x4 rotationX, rotationY, rotationZ;

    double radianX = degrees_to_radians(angleX);
    double radianY = degrees_to_radians(angleY);
    double radianZ = degrees_to_radians(angleZ);

    rotationX.set(1, 1, std::cos(radianX));
    rotationX.set(1, 2, -std::sin(radianX));
    rotationX.set(2, 1, std::sin(radianX));
    rotationX.set(2, 2, std::cos(radianX));

    rotationY.set(0, 0, std::cos(radianY));
    rotationY.set(0, 2, std::sin(radianY));
    rotationY.set(2, 0, -std::sin(radianY));
    rotationY.set(2, 2, std::cos(radianY));

    rotationZ.set(0, 0, std::cos(radianZ));
    rotationZ.set(0, 1, -std::sin(radianZ));
    rotationZ.set(1, 0, std::sin(radianZ));
    rotationZ.set(1, 1, std::cos(radianZ));

    Matrix4x4 combinedRotation = rotationZ * rotationY * rotationX;

    camera_to_world = combinedRotation * camera_to_world;
}
}  // namespace RayTracer
