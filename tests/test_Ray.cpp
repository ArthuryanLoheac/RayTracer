#include <criterion/criterion.h>
#include "3dDatas/Ray.hpp"

Test(Ray, default_constructor) {
    RayTracer::Ray ray;
    cr_assert_eq(ray.origin.x, 0);
    cr_assert_eq(ray.origin.y, 0);
    cr_assert_eq(ray.origin.z, 0);
    cr_assert_eq(ray.direction.x, 0);
    cr_assert_eq(ray.direction.y, 0);
    cr_assert_eq(ray.direction.z, 0);
}

Test(Ray, parameterized_constructor) {
    RayTracer::Point3D origin(1.0, 2.0, 3.0);
    RayTracer::Vector3D direction(4.0, 5.0, 6.0);
    RayTracer::Ray ray(origin, direction);
    cr_assert_eq(ray.origin.x, 1.0);
    cr_assert_eq(ray.origin.y, 2.0);
    cr_assert_eq(ray.origin.z, 3.0);
    cr_assert_eq(ray.direction.x, 4.0);
    cr_assert_eq(ray.direction.y, 5.0);
    cr_assert_eq(ray.direction.z, 6.0);
}

Test(Ray, normalized) {
    RayTracer::Point3D origin(0.0, 0.0, 0.0);
    RayTracer::Vector3D direction(3.0, 4.0, 0.0);
    RayTracer::Ray ray(origin, direction);
    ray.normalized();
    cr_assert_float_eq(ray.direction.length(), 1.0, 1e-6);
}
