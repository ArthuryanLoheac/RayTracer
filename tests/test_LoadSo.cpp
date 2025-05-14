#include <criterion/criterion.h>
#include <memory>
#include <string>
#include "3dDatas/Point3D.hpp"
#include "3dDatas/Vector3D.hpp"
#include "dlLoader/dlLoader.hpp"
#include "Interfaces/Primitive/I_Primitive.hpp"
#include "Interfaces/Material/I_Material.hpp"
#include "Interfaces/Light/I_Light.hpp"

static std::shared_ptr<RayTracer::I_Primitive> getPrimitive(std::string libName) {
    return dlLoader<RayTracer::I_Primitive>::getLib("./plugins/" + libName, "getPrimitive");
}

static std::shared_ptr<RayTracer::I_Material> getMaterial(std::string libName) {
    return dlLoader<RayTracer::I_Material>::getLib("./plugins/" + libName, "getMaterial");
}

static std::shared_ptr<RayTracer::I_Light> getLight(std::string libName) {
    return dlLoader<RayTracer::I_Light>::getLib("./plugins/" + libName, "getLight");
}

Test(LoadSo, PrimitiveSphere) {
    try {
        std::shared_ptr<RayTracer::I_Primitive> prim = getPrimitive("primitive_sphere.so");
        cr_assert_not_null(prim);
    } catch (std::exception &e) {
        cr_assert_fail("Failed to load primitive_sphere.so");
    }
}

Test(LoadSo, PrimitiveCylinder) {
    try {
        std::shared_ptr<RayTracer::I_Primitive> prim = getPrimitive("primitive_cylinder.so");
        cr_assert_not_null(prim);
    } catch (std::exception &e) {
        cr_assert_fail("Failed to load primitive_cylinder.so");
    }
}

Test(LoadSo, PrimitivePlane) {
    try {
        std::shared_ptr<RayTracer::I_Primitive> prim = getPrimitive("primitive_plane.so");
        cr_assert_not_null(prim);
    } catch (std::exception &e) {
        cr_assert_fail("Failed to load primitive_plane.so");
    }
}

Test(LoadSo, PrimitiveNone) {
    try {
        std::shared_ptr<RayTracer::I_Primitive> prim = getPrimitive("primitive_none.so");
        cr_assert_not_null(prim);
    } catch (std::exception &e) {
        cr_assert_fail("Failed to load primitive_none.so");
    }
}

Test(LoadSo, MaterialFlat) {
    try {
        std::shared_ptr<RayTracer::I_Material> mat = getMaterial("mat_flat.so");
        cr_assert_not_null(mat);
    } catch (std::exception &e) {
        cr_assert_fail("Failed to load mat_flat.so");
    }
}

Test(LoadSo, LightAmbient) {
    try {
        std::shared_ptr<RayTracer::I_Light> light = getLight("light_ambient.so");
        cr_assert_not_null(light);
    } catch (std::exception &e) {
        cr_assert_fail("Failed to load light_ambient.so");
    }
}

Test(LoadSo, LightSpot) {
    try {
        std::shared_ptr<RayTracer::I_Light> light = getLight("light_spot.so");
        cr_assert_not_null(light);
    } catch (std::exception &e) {
        cr_assert_fail("Failed to load light_spot.so");
    }
}
