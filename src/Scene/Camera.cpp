#include "Scene/Camera.hpp"
#include "Consts/const.hpp"
#include <cmath>
#include <iostream>

namespace RayTracer {
static double degrees_to_radians(double degrees) {
    return degrees * M_PI / 180.0;
}

Camera::Camera() {
    aspect_ratio = 1;
    image_width = 800;
    vfov = 90;
    origin = Point3D(0, 0, 3);
    lookingAt = Point3D(0, 0, 2);
    Vector3D rotation = Point3D(-1, 0, 0);

    image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    auto focal_length = Vector3D(origin - lookingAt).length();
    auto theta = degrees_to_radians(vfov);
    auto h = std::tan(theta/2);
    auto viewport_height = 2 * h * focal_length;
    auto viewport_width = viewport_height * (double(image_width)/image_height);


    std::cout << Vector3D(1, rotation.y, rotation.z).normalized() * viewport_width << std::endl;
    std::cout << Vector3D(rotation.x, 1, rotation.z).normalized() * -viewport_height << std::endl;

    screen = Rectangle3D(
        Point3D(origin.x + -viewport_width / 2,
            origin.y +  viewport_height / 2,
            origin.z +  focal_length),
        Vector3D(1, 0, 0).normalized() * viewport_width,
        Vector3D(0, 1, 0).normalized() * -viewport_height);
}

Ray Camera::ray(double u, double v) {
    Point3D p = screen.pointAt(u, v);
    Vector3D v2 = {
        p.x - origin.x,
        p.y - origin.y,
        p.z - origin.z
    };
    v2 /= v2.length();
    return Ray(origin, v2);
}
}  // namespace RayTracer
