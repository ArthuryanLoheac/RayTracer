#pragma once
#include <cmath>
#include <ostream>

#include "3dDatas/Point3D.hpp"

namespace RayTracer {

class Point3D;
class Vector3D {
 public:
    double x, y, z;
    Vector3D();
    explicit Vector3D(Point3D point);
    Vector3D(double x, double y, double z);

    double length();
    double dot(const Vector3D& other);
    Vector3D &normalize();
    Vector3D normalized();
    Vector3D cross(const Vector3D& u);

    // Vector3D
    Vector3D operator+(const Vector3D& other);
    Vector3D &operator+=(const Vector3D& other);
    Vector3D operator-(const Vector3D& other);
    Vector3D operator-(const Point3D& other);
    Vector3D &operator-=(const Vector3D& other);
    Vector3D operator*(const Vector3D& other);
    Vector3D &operator*=(const Vector3D& other);
    Vector3D operator/(const Vector3D& other);
    Vector3D &operator/=(const Vector3D& other);
    // Double
    Vector3D operator*(double other);
    Vector3D &operator*=(double other);
    Vector3D operator/(double other);
    Vector3D &operator/=(double other);

    Vector3D &operator=(Point3D other);

    float lengthSquared();
};
}  // namespace RayTracer

std::ostream& operator<<(std::ostream& os, const RayTracer::Vector3D &vec);
