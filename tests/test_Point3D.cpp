#include <criterion/criterion.h>
#include "3dDatas/Point3D.hpp"
#include "3dDatas/Vector3D.hpp"

Test(Point3D, default_constructor) {
    RayTracer::Point3D point;
    cr_assert_eq(point.x, 0);
    cr_assert_eq(point.y, 0);
    cr_assert_eq(point.z, 0);
}

Test(Point3D, parameterized_constructor) {
    RayTracer::Point3D point(1.0, 2.0, 3.0);
    cr_assert_eq(point.x, 1.0);
    cr_assert_eq(point.y, 2.0);
    cr_assert_eq(point.z, 3.0);
}

Test(Point3D, addition_with_vector) {
    RayTracer::Point3D point(1.0, 2.0, 3.0);
    RayTracer::Vector3D vec(4.0, 5.0, 6.0);
    RayTracer::Point3D result = point + vec;
    cr_assert_eq(result.x, 5.0);
    cr_assert_eq(result.y, 7.0);
    cr_assert_eq(result.z, 9.0);
}

Test(Point3D, addition_with_point) {
    RayTracer::Point3D point1(1.0, 2.0, 3.0);
    RayTracer::Point3D point2(4.0, 5.0, 6.0);
    RayTracer::Point3D result = point1 + point2;
    cr_assert_eq(result.x, 5.0);
    cr_assert_eq(result.y, 7.0);
    cr_assert_eq(result.z, 9.0);
}

Test(Point3D, subtraction_with_vector) {
    RayTracer::Point3D point(1.0, 2.0, 3.0);
    RayTracer::Vector3D vec(4.0, 5.0, 6.0);
    RayTracer::Point3D result = point - vec;
    cr_assert_eq(result.x, -3.0);
    cr_assert_eq(result.y, -3.0);
    cr_assert_eq(result.z, -3.0);
}

Test(Point3D, subtraction_with_point) {
    RayTracer::Point3D point1(1.0, 2.0, 3.0);
    RayTracer::Point3D point2(4.0, 5.0, 6.0);
    RayTracer::Vector3D result = point1 - point2;
    cr_assert_eq(result.x, -3.0);
    cr_assert_eq(result.y, -3.0);
    cr_assert_eq(result.z, -3.0);
}

Test(Point3D, distance) {
    RayTracer::Point3D point1(1.0, 2.0, 3.0);
    RayTracer::Point3D point2(4.0, 6.0, 3.0);
    float dist = point1.distance(point2);
    cr_assert_float_eq(dist, 5.0, 1e-6);
}

Test(Point3D, ostream_operator) {
    RayTracer::Point3D point(1.0, 2.0, 3.0);
    std::ostringstream oss;
    oss << point;
    cr_assert_eq(oss.str(), "P(1, 2, 3)");
}
