#include "Scene/Camera.hpp"
#include "Consts/const.hpp"
#include <cmath>
#include <iostream>

// ATENTION Camera position depends on  orientation

namespace RayTracer {
static double degrees_to_radians(double degrees) {
    return degrees * M_PI / 180.0;
}

Camera::Camera() {
    aspect_ratio = 1;
    image_width = 800;
    vfov = 90;
    origin = Point3D(0, 0, 0);
    lookingAt = origin + Point3D(0, 0, 1);

    image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    auto focal_length = Vector3D(origin - lookingAt).length();
    auto theta = degrees_to_radians(vfov);
    auto h = std::tan(theta/2);
    auto viewport_height = 2 * h * focal_length;
    auto viewport_width = viewport_height * (double(image_width)/image_height);
    rotate(0, 0, 0);

    screen = Rectangle3D(
        Point3D(origin.x + -viewport_width / 2,
            origin.y +  viewport_height / 2,
            origin.z +  focal_length),
        Vector3D(1, 0, 0).normalized() * viewport_width,
        Vector3D(0, -1, 0).normalized() * viewport_height);
}

Ray Camera::ray(double u, double v) {
    Point3D p = screen.pointAt(u, v);
    Point3D origin_world = camera_to_world.transformPoint(origin);
    Point3D p_world = camera_to_world.transformPoint(p);
    Vector3D ray_direction = (p_world - origin_world).normalized();

    return Ray(origin_world, ray_direction);
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
