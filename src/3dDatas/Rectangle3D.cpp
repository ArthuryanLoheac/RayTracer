#include "3dDatas/Rectangle3D.hpp"

namespace RayTracer {

Rectangle3D::Rectangle3D() {
    origin = Point3D(0, 0, 0);
    bottom_side = Vector3D(1, 0, 0);
    left_side = Vector3D(0, 1, 0);
}

Rectangle3D::Rectangle3D
(Point3D origin, Vector3D bottom_side, Vector3D left_side) {
    this->origin = origin;
    this->bottom_side = bottom_side;
    this->left_side = left_side;
}

Point3D Rectangle3D::pointAt(double u, double v) {
    return Point3D(origin.x + bottom_side.x * u + left_side.x * v,
                   origin.y + bottom_side.y * u + left_side.y * v,
                   origin.z + bottom_side.z * u + left_side.z * v);
}
}  // namespace RayTracer
