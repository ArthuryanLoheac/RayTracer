#include "Scene/Camera.hpp"
#include "Consts/const.hpp"

namespace RayTracer {

Camera::Camera() {
    double aspect_ratio = static_cast<double>(WIDTH) / HEIGHT;
    double viewport_height = 2.0;  // Default viewport height
    double viewport_width = viewport_height * aspect_ratio;
    double focal_length = 1.0;  // Distance from camera to screen

    origin = Point3D(0, 0, 0);

    screen = Rectangle3D(
        Point3D(origin.x + -viewport_width / 2,
            origin.y +  viewport_height / 2,
            origin.z +  focal_length),
        Vector3D(viewport_width, 0, 0),
        Vector3D(0, -viewport_height, 0));
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
