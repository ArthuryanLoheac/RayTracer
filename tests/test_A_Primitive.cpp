#include <criterion/criterion.h>
#include <memory>
#include "Interfaces/Primitive/A_Primitive.hpp"
#include "3dDatas/Point3D.hpp"
#include "3dDatas/Vector3D.hpp"

class TestPrimitive : public RayTracer::A_Primitive {
 public:
    bool hits(RayTracer::Ray ray, RayTracer::Point3D &intersection) override {
        (void)ray;
        (void)intersection;
        return false;
    }
    RayTracer::Vector3D getNormalAt(RayTracer::Point3D point) override {
        (void)point;
        return RayTracer::Vector3D(0, 0, 0);
    }
    void Init() override {}
};

Test(A_Primitive, AddChildren) {
    std::shared_ptr<RayTracer::A_Primitive> parent = std::make_shared<TestPrimitive>();
    std::shared_ptr<RayTracer::A_Primitive> child = std::make_shared<TestPrimitive>();

    parent->AddChildren(child);
    cr_assert_eq(parent->getChildrens().size(), 1);
    cr_assert_eq(parent->getChildrens()[0], child);
}

Test(A_Primitive, SetAndGetMaterial) {
    std::shared_ptr<RayTracer::A_Primitive> primitive = std::make_shared<TestPrimitive>();
    std::shared_ptr<RayTracer::I_Material> material = nullptr;

    cr_assert_throw(primitive->getMaterial(), RayTracer::A_Primitive::PrimitiveError);
    primitive->setMaterial(material);
    cr_assert_throw(primitive->getMaterial(), RayTracer::A_Primitive::PrimitiveError);
}

Test(A_Primitive, SetAndGetPosition) {
    std::shared_ptr<RayTracer::A_Primitive> primitive = std::make_shared<TestPrimitive>();
    RayTracer::Point3D position(1, 2, 3);

    primitive->setPosition(position);
    cr_assert_eq(primitive->getPosition().x, 1);
    cr_assert_eq(primitive->getPosition().y, 2);
    cr_assert_eq(primitive->getPosition().z, 3);
}

Test(A_Primitive, SetAndGetRotation) {
    std::shared_ptr<RayTracer::A_Primitive> primitive = std::make_shared<TestPrimitive>();
    RayTracer::Vector3D rotation(10, 20, 30);

    primitive->setRotation(rotation);
    cr_assert_eq(primitive->getRotation().x, 10);
    cr_assert_eq(primitive->getRotation().y, 20);
    cr_assert_eq(primitive->getRotation().z, 30);
}

Test(A_Primitive, SetAndGetScale) {
    std::shared_ptr<RayTracer::A_Primitive> primitive = std::make_shared<TestPrimitive>();
    RayTracer::Point3D scale(2, 2, 2);

    primitive->setScale(scale);
    cr_assert_eq(primitive->getScale().x, 2);
    cr_assert_eq(primitive->getScale().y, 2);
    cr_assert_eq(primitive->getScale().z, 2);
}
