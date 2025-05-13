#pragma once
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include <array>

namespace RayTracer {
class Matrix4x4 {
 private:
    std::array<std::array<double, 4>, 4> m;

 public:
    Matrix4x4() {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                m[i][j] = (i == j) ? 1.0 : 0.0;  // Identity matrix
    }

    void set(int row, int col, double value) {
        m[row][col] = value;
    }

    Point3D transformPoint(const Point3D& p) const {
        double x = m[0][0] * p.x + m[0][1] * p.y + m[0][2] * p.z + m[0][3];
        double y = m[1][0] * p.x + m[1][1] * p.y + m[1][2] * p.z + m[1][3];
        double z = m[2][0] * p.x + m[2][1] * p.y + m[2][2] * p.z + m[2][3];
        return Point3D(x, y, z);
    }

    Vector3D transformVector(const Vector3D& v) const {
        double x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z;
        double y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z;
        double z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z;
        return Vector3D(x, y, z);
    }

    // Overload the multiplication operator for matrix multiplication
    Matrix4x4 operator*(const Matrix4x4& other) const {
        Matrix4x4 result;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                result.m[i][j] = 0;
                for (int k = 0; k < 4; ++k) {
                    result.m[i][j] += m[i][k] * other.m[k][j];
                }
            }
        }
        return result;
    }
};
}  // namespace RayTracer
