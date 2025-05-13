#include "3dDatas/Vector3D.hpp"

#pragma region CONSTRUCTORS

RayTracer::Vector3D::Vector3D() {
    x = 0;
    y = 0;
    z = 0;
}

RayTracer::Vector3D::Vector3D(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}
RayTracer::Vector3D::Vector3D(Point3D other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
}

#pragma endregion CONSTRUCTORS
#pragma region TOOLS

double RayTracer::Vector3D::length() {
    return std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
}

double RayTracer::Vector3D::dot(const Vector3D &other) {
    return x * other.x + y * other.y + z * other.z;
}

RayTracer::Vector3D &RayTracer::Vector3D::normalize() {
    double len = length();
    if (len != 0) {
        x /= len;
        y /= len;
        z /= len;
    }
    return *this;
}

RayTracer::Vector3D RayTracer::Vector3D::normalized() {
    double len = length();
    return RayTracer::Vector3D(x / len, y / len, z / len);
}

RayTracer::Vector3D RayTracer::Vector3D::cross(const Vector3D &v) {
    return Vector3D(y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x);
}

#pragma endregion TOOLS
#pragma region OPERATORS

        // Add Vector3D
        RayTracer::Vector3D RayTracer::Vector3D::
        operator+
    (const RayTracer::Vector3D &other) {
    return Vector3D(x + other.x, y + other.y, z +  other.z);
}

RayTracer::Vector3D &RayTracer::Vector3D::operator+=
 (const RayTracer::Vector3D &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

// Substract Vector3D
RayTracer::Vector3D RayTracer::Vector3D::operator-(const Vector3D& other) {
    return Vector3D(x - other.x, y - other.y, z -  other.z);
}

RayTracer::Vector3D RayTracer::Vector3D::operator-(const Point3D& other) {
    return Vector3D(x - other.x, y - other.y, z -  other.z);
}

RayTracer::Vector3D &RayTracer::Vector3D::operator-=
 (const RayTracer::Vector3D &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

// Mutliply Vector3D
RayTracer::Vector3D RayTracer::Vector3D::operator*(const Vector3D& other) {
    return Vector3D(x * other.x, y * other.y, z *  other.z);
}

RayTracer::Vector3D &RayTracer::Vector3D::operator*=
 (const RayTracer::Vector3D &other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}

// Divide Vector3D
RayTracer::Vector3D RayTracer::Vector3D::operator/(const Vector3D& other) {
    return Vector3D(x / other.x, y / other.y, z /  other.z);
}

RayTracer::Vector3D &RayTracer::Vector3D::operator/=
 (const RayTracer::Vector3D &other) {
    x /= other.x;
    y /= other.y;
    z /= other.z;
    return *this;
}

// Multiply double
RayTracer::Vector3D RayTracer::Vector3D::operator*(double other) {
    return Vector3D(x * other, y * other, z *  other);
}

RayTracer::Vector3D &RayTracer::Vector3D::operator*=(double other) {
    x *= other;
    y *= other;
    z *= other;
    return *this;
}

// Dividide double
RayTracer::Vector3D RayTracer::Vector3D::operator/(double other) {
    return Vector3D(x / other, y / other, z /  other);
}

RayTracer::Vector3D &RayTracer::Vector3D::operator/=(double other) {
    x /= other;
    y /= other;
    z /= other;
    return *this;
}

RayTracer::Vector3D &RayTracer::Vector3D::operator=(Point3D other) {
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const RayTracer::Vector3D &vec) {
    os << "V(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}

#pragma endregion OPERATORS
