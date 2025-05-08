#include <criterion/criterion.h>
#include "3dDatas/Vector3D.hpp"

Test(Vector3D, default_constructor) {
    RayTracer::Vector3D vec;
    cr_assert_eq(vec.x, 0);
    cr_assert_eq(vec.y, 0);
    cr_assert_eq(vec.z, 0);
}

Test(Vector3D, parameterized_constructor) {
    RayTracer::Vector3D vec(1.0, 2.0, 3.0);
    cr_assert_eq(vec.x, 1.0);
    cr_assert_eq(vec.y, 2.0);
    cr_assert_eq(vec.z, 3.0);
}

Test(Vector3D, length) {
    RayTracer::Vector3D vec(3.0, 4.0, 0.0);
    cr_assert_float_eq(vec.length(), 5.0, 1e-6);
}

Test(Vector3D, dot_product) {
    RayTracer::Vector3D vec1(1.0, 2.0, 3.0);
    RayTracer::Vector3D vec2(4.0, -5.0, 6.0);
    cr_assert_float_eq(vec1.dot(vec2), 12.0, 1e-6);
}

Test(Vector3D, normalize) {
    RayTracer::Vector3D vec(3.0, 4.0, 0.0);
    vec.normalize();
    cr_assert_float_eq(vec.length(), 1.0, 1e-6);
}

Test(Vector3D, addition_operator) {
    RayTracer::Vector3D vec1(1.0, 2.0, 3.0);
    RayTracer::Vector3D vec2(4.0, 5.0, 6.0);
    RayTracer::Vector3D result = vec1 + vec2;
    cr_assert_eq(result.x, 5.0);
    cr_assert_eq(result.y, 7.0);
    cr_assert_eq(result.z, 9.0);
}

Test(Vector3D, subtraction_operator) {
    RayTracer::Vector3D vec1(1.0, 2.0, 3.0);
    RayTracer::Vector3D vec2(4.0, 5.0, 6.0);
    RayTracer::Vector3D result = vec1 - vec2;
    cr_assert_eq(result.x, -3.0);
    cr_assert_eq(result.y, -3.0);
    cr_assert_eq(result.z, -3.0);
}

Test(Vector3D, multiplication_operator) {
    RayTracer::Vector3D vec1(1.0, 2.0, 3.0);
    RayTracer::Vector3D vec2(4.0, 5.0, 6.0);
    RayTracer::Vector3D result = vec1 * vec2;
    cr_assert_eq(result.x, 4.0);
    cr_assert_eq(result.y, 10.0);
    cr_assert_eq(result.z, 18.0);
}

Test(Vector3D, division_operator) {
    RayTracer::Vector3D vec1(4.0, 10.0, 18.0);
    RayTracer::Vector3D vec2(2.0, 5.0, 3.0);
    RayTracer::Vector3D result = vec1 / vec2;
    cr_assert_eq(result.x, 2.0);
    cr_assert_eq(result.y, 2.0);
    cr_assert_eq(result.z, 6.0);
}

Test(Vector3D, scalar_multiplication) {
    RayTracer::Vector3D vec(1.0, 2.0, 3.0);
    RayTracer::Vector3D result = vec * 2.0;
    cr_assert_eq(result.x, 2.0);
    cr_assert_eq(result.y, 4.0);
    cr_assert_eq(result.z, 6.0);
}

Test(Vector3D, scalar_division) {
    RayTracer::Vector3D vec(2.0, 4.0, 6.0);
    RayTracer::Vector3D result = vec / 2.0;
    cr_assert_eq(result.x, 1.0);
    cr_assert_eq(result.y, 2.0);
    cr_assert_eq(result.z, 3.0);
}

Test(Vector3D, assignment_from_point) {
    RayTracer::Point3D point(1.0, 2.0, 3.0);
    RayTracer::Vector3D vec;
    vec = point;
    cr_assert_eq(vec.x, 1.0);
    cr_assert_eq(vec.y, 2.0);
    cr_assert_eq(vec.z, 3.0);
}
