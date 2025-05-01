#include "3dDatas/Vector3D.hpp"
#include "Primitive/I_Primitive.hpp"
#include "3dDatas/Point3D.hpp"
#include "Consts/const.hpp"

void computeTreeValues(std::shared_ptr<Prim> head) {
    if (head->getParent() != nullptr) {
        head->getPosition() = head->getPosition() +
            head->getParent()->getPosition();
    }
    for (std::shared_ptr<Prim> &o : head->getChildrens())
        computeTreeValues(o);
}
