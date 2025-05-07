#include <criterion/criterion.h>
#include <memory>

#include "Scene/Scene.hpp"
#include "Lights/Spot.hpp"
#include "Generation/tools.hpp"
#include "dlLoader/dlLoader.hpp"

static std::shared_ptr<RayTracer::I_Primitive> getPrimitive(std::string libName) {
    return dlLoader<RayTracer::I_Primitive>::getLib("./libs/" + libName, "getPrimitive");
}

Test(ComputeTreeValues, update_positions) {
    RayTracer::Scene scene;
    RayTracer::Scene::i = &scene;
    RayTracer::Point3D posOriginal;

    auto parent = getPrimitive("primitive_sphere.so");
    parent->setPosition(RayTracer::Point3D(10, 10, 10));

    auto child = getPrimitive("primitive_sphere.so");
    parent->AddChildren(child);
    posOriginal = child->getPosition();

    computeTreeValues(parent);

    cr_assert_eq(child->getPosition().x, posOriginal.x + 10, "Child X position incorrect : %f", child->getPosition().x);
    cr_assert_eq(child->getPosition().y, posOriginal.y + 10, "Child Y position incorrect : %f", child->getPosition().y);
    cr_assert_eq(child->getPosition().z, posOriginal.z + 10, "Child Z position incorrect : %f", child->getPosition().z);
}
