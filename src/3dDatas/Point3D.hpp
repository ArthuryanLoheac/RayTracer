#pragma once
#include <ostream>
#include "3dDatas/Vector3D.hpp"

namespace RayTracer {
class Vector3D;
class Point3D {
 public:
    double x, y, z;
    Point3D();
    Point3D(double x, double y, double z);
    double length();

    Point3D operator+(const Vector3D& vec);
    Point3D operator+(const Point3D& other);
    Point3D operator-(const Vector3D& vec);
    Vector3D operator-(const Point3D& vec);
    Point3D operator*(float scalar) const;
    Point3D operator/(float scalar) const;
    bool operator==(const Point3D& other);
    bool operator!=(const Point3D& other);

    float distance(Point3D other);
};
}  // namespace RayTracer

std::ostream& operator<<(std::ostream& os, const RayTracer::Point3D& point);
