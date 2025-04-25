#pragma once
#include <cmath>
#include <ostream>

namespace RayTracer {
class Vector3D {
 public:
    double x, y, z;
    Vector3D();
    Vector3D(double x, double y, double z);

    double length();
    double dot(const Vector3D& other);

    // Vector3D
    Vector3D operator+(const Vector3D& other);
    Vector3D &operator+=(const Vector3D& other);
    Vector3D operator-(const Vector3D& other);
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
};
}  // namespace RayTracer

std::ostream& operator<<(std::ostream& os, const RayTracer::Vector3D &vec);
