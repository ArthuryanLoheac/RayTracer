#include "A_Primitive.hpp"

namespace RayTracer {

std::shared_ptr<I_Primitive> RayTracer::A_Primitive::getParent() {
    return parent;
}

void RayTracer::A_Primitive::setParent(std::shared_ptr<I_Primitive> parent) {
    this->parent = parent;
}

std::vector<std::shared_ptr<I_Primitive>> &RayTracer::A_Primitive::getChildrens() {
    return childrens;
}

void RayTracer::A_Primitive::AddChildren(std::shared_ptr<I_Primitive> child) {
    childrens.push_back(child);
}

std::shared_ptr<I_Material> RayTracer::A_Primitive::getMaterial() {
    return material;
}

Point3D RayTracer::A_Primitive::getPosition() {
    return position;
}

Point3D RayTracer::A_Primitive::getRotation() {
    return rotation;
}

Point3D RayTracer::A_Primitive::getScale() {
    return scale;
}

}  // namespace RayTracer