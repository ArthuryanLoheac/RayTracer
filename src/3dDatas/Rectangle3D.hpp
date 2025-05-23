#ifndef SRC_3DDATAS_RECTANGLE3D_HPP_
#define SRC_3DDATAS_RECTANGLE3D_HPP_

#include "3dDatas/Point3D.hpp"
#include "3dDatas/Vector3D.hpp"

namespace RayTracer {
class Rectangle3D {
 public:
    Point3D origin;
    Vector3D bottom_side;
    Vector3D left_side;

    Rectangle3D();
    Rectangle3D(Point3D origin, Vector3D bottom_side, Vector3D left_side);
    Point3D pointAt(double u, double v);
};
}  // namespace RayTracer
#endif  // SRC_3DDATAS_RECTANGLE3D_HPP_"
