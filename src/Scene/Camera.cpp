#include "Scene/Camera.hpp"
#include "Consts/const.hpp"

namespace RayTracer {

Camera::Camera() {
    double aspect_ratio = static_cast<double>(WIDTH) / HEIGHT;
    screen = Rectangle3D(Point3D(0, 0, -5),
        Vector3D(aspect_ratio, 0, 0),
        Vector3D(0, 1, 0));
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
