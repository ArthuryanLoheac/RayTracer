#include <criterion/criterion.h>
#include <memory>
#include "Interfaces/Light/A_Light.hpp"
#include "3dDatas/Point3D.hpp"
#include "3dDatas/Vector3D.hpp"
#include "Draw/hit.hpp"

class TestLight : public RayTracer::A_Lights {
 public:
    float getLuminescence(hitDatas datas,
        std::shared_ptr<I_Light> Light,
        std::shared_ptr<I_Primitive> head) override {
        (void)datas;
        (void)Light;
        (void)head;
        return intensity;
    }
    void Init(std::unordered_map<std::string, std::any> &settings) override {
        (void)settings;
    }
};

Test(A_Light, SetAndGetPosition) {
    std::shared_ptr<RayTracer::A_Lights> light = std::make_shared<TestLight>();
    RayTracer::Point3D position(1, 2, 3);

    light->setPosition(position);
    cr_assert_eq(light->getPosition().x, 1);
    cr_assert_eq(light->getPosition().y, 2);
    cr_assert_eq(light->getPosition().z, 3);
}

Test(A_Light, SetAndGetRotation) {
    std::shared_ptr<RayTracer::A_Lights> light = std::make_shared<TestLight>();
    RayTracer::Vector3D rotation(10, 20, 30);

    light->setRotation(rotation);
    cr_assert_eq(light->getRotation().x, 10);
    cr_assert_eq(light->getRotation().y, 20);
    cr_assert_eq(light->getRotation().z, 30);
}

Test(A_Light, SetAndGetScale) {
    std::shared_ptr<RayTracer::A_Lights> light = std::make_shared<TestLight>();
    RayTracer::Point3D scale(2, 2, 2);

    light->setScale(scale);
    cr_assert_eq(light->getScale().x, 2);
    cr_assert_eq(light->getScale().y, 2);
    cr_assert_eq(light->getScale().z, 2);
}
