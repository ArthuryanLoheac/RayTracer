#include "3dDatas/Point3D.hpp"

RayTracer::Point3D::Point3D()
: x(0), y(0), z(0) {}

RayTracer::Point3D::Point3D(double x, double y, double z)
    : x(x), y(y), z(z) {}

RayTracer::Point3D RayTracer::Point3D::operator+(const Vector3D &vec) {
    return Point3D(x + vec.x, y + vec.y, z + vec.z);
}

RayTracer::Point3D RayTracer::Point3D::operator+(const Point3D &other) {
    return Point3D(x + other.x, y + other.y, z + other.z);
}

RayTracer::Point3D RayTracer::Point3D::operator-(const Vector3D &vec) {
    return Point3D(x - vec.x, y - vec.y, z - vec.z);
}

RayTracer::Vector3D RayTracer::Point3D::operator-(const Point3D &vec) {
    return Vector3D(x - vec.x, y - vec.y, z - vec.z);
}

float RayTracer::Point3D::distance(Point3D other) {
    return std::sqrt(std::pow(x - other.x, 2) +
                    std::pow(y - other.y, 2) +
                    std::pow(z - other.z, 2));
}

std::ostream &operator<<(std::ostream &os, const RayTracer::Point3D &point) {
    os << "P(" << point.x << ", " << point.y << ", " << point.z << ")";
    return os;
}
