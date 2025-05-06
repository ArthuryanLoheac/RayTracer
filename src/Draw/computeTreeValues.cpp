#include <memory>

#include "3dDatas/Vector3D.hpp"
#include "Primitive/I_Primitive.hpp"
#include "3dDatas/Point3D.hpp"
#include "Consts/const.hpp"
#include "Scene/Scene.hpp"

void computeTreeValues(std::shared_ptr<Prim> head,
std::shared_ptr<Prim> parent) {
    if (parent != nullptr)
        head->setPosition(head->getPosition() + parent->getPosition());
    if (dynamic_cast<Light *>(head.get()) != nullptr) {
        RayTracer::Scene::i->Lights.push_back(
            std::shared_ptr<Light>(dynamic_cast<Light *>(head.get())));
    }
    for (std::shared_ptr<Prim> &o : head->getChildrens())
        computeTreeValues(o, head);
}
