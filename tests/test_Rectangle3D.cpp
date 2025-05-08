#include <criterion/criterion.h>
#include "3dDatas/Rectangle3D.hpp"

Test(Rectangle3D, default_constructor) {
    RayTracer::Rectangle3D rect;
    cr_assert_eq(rect.origin.x, 0);
    cr_assert_eq(rect.origin.y, 0);
    cr_assert_eq(rect.origin.z, 0);
    cr_assert_eq(rect.bottom_side.x, 1);
    cr_assert_eq(rect.bottom_side.y, 0);
    cr_assert_eq(rect.bottom_side.z, 0);
    cr_assert_eq(rect.left_side.x, 0);
    cr_assert_eq(rect.left_side.y, 1);
    cr_assert_eq(rect.left_side.z, 0);
}

Test(Rectangle3D, parameterized_constructor) {
    RayTracer::Point3D origin(1.0, 2.0, 3.0);
    RayTracer::Vector3D bottom(4.0, 5.0, 6.0);
    RayTracer::Vector3D left(7.0, 8.0, 9.0);
    RayTracer::Rectangle3D rect(origin, bottom, left);
    cr_assert_eq(rect.origin.x, 1.0);
    cr_assert_eq(rect.origin.y, 2.0);
    cr_assert_eq(rect.origin.z, 3.0);
    cr_assert_eq(rect.bottom_side.x, 4.0);
    cr_assert_eq(rect.bottom_side.y, 5.0);
    cr_assert_eq(rect.bottom_side.z, 6.0);
    cr_assert_eq(rect.left_side.x, 7.0);
    cr_assert_eq(rect.left_side.y, 8.0);
    cr_assert_eq(rect.left_side.z, 9.0);
}

Test(Rectangle3D, pointAt) {
    RayTracer::Point3D origin(0.0, 0.0, 0.0);
    RayTracer::Vector3D bottom(1.0, 0.0, 0.0);
    RayTracer::Vector3D left(0.0, 1.0, 0.0);
    RayTracer::Rectangle3D rect(origin, bottom, left);
    RayTracer::Point3D point = rect.pointAt(2.0, 3.0);
    cr_assert_eq(point.x, 2.0);
    cr_assert_eq(point.y, 3.0);
    cr_assert_eq(point.z, 0.0);
}
