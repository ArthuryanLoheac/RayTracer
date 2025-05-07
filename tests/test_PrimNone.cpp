#include <criterion/criterion.h>
#include <memory>
#include <string>
#include "3dDatas/Point3D.hpp"
#include "3dDatas/Vector3D.hpp"
#include "dlLoader/dlLoader.hpp"
#include "Interfaces/Primitive/I_Primitive.hpp"

static std::shared_ptr<RayTracer::I_Primitive> getPrimitive
(std::string libName) {
    return dlLoader<RayTracer::I_Primitive>::getLib("./libs/"
    + libName, "getPrimitive");
}

Test(I_Primitive, PrimNone) {
    try {
        std::shared_ptr<RayTracer::I_Primitive> prim =
            getPrimitive("primitive_none.so");
        cr_assert_not_null(prim);
    } catch (std::exception &e) {
        cr_assert_fail("Failed to load the library or get the primitive");
    }
}

Test(I_Primitive, Hits) {
    try {
        std::shared_ptr<RayTracer::I_Primitive> prim =
            getPrimitive("primitive_none.so");
        prim->Init();
        RayTracer::Ray ray;
        RayTracer::Point3D p(0, 0, 0);
        cr_assert(prim->hits(ray, p) == false);
        p.z = 1;
        ray.direction = RayTracer::Vector3D(0, 0, 1);
        cr_assert(prim->hits(ray, p) == false);
    } catch (std::exception &e) {
        cr_assert_fail("Failed to load the library or get the primitive");
    }
}

Test(I_Primitive, GetNormalAt) {
    try {
        std::shared_ptr<RayTracer::I_Primitive> prim =
            getPrimitive("primitive_none.so");
        prim->Init();
        RayTracer::Ray ray;
        RayTracer::Point3D p(0, 0, 0);
        RayTracer::Vector3D norm = prim->getNormalAt(p);
        cr_assert_eq(norm.x, 0);
        cr_assert_eq(norm.y, 0);
        cr_assert_eq(norm.z, 0);
        p.z = 1;
        ray.direction = RayTracer::Vector3D(0, 0, 1);
        norm = prim->getNormalAt(p);
        cr_assert_eq(norm.x, 0);
        cr_assert_eq(norm.y, 0);
        cr_assert_eq(norm.z, 0);
    } catch (std::exception &e) {
        cr_assert_fail("Failed to load the library or get the primitive");
    }
}
