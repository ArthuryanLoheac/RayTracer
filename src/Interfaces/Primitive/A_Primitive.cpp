#include <memory>
#include <vector>
#include <string>

#include "Interfaces/Primitive/A_Primitive.hpp"

namespace RayTracer {

std::vector<std::shared_ptr<I_Primitive>>
&RayTracer::A_Primitive::getChildrens() {
    return childrens;
}

std::shared_ptr<I_Primitive> &RayTracer::A_Primitive::AddChildren(
    std::shared_ptr<I_Primitive> child) {
    childrens.push_back(child);
    return childrens.back();
}

std::shared_ptr<I_Material> RayTracer::A_Primitive::getMaterial() {
    if (!material)
        throw PrimitiveError("Material not set");
    return material;
}

void A_Primitive::setMaterial(std::shared_ptr<I_Material> material) {
    this->material = material;
}

Point3D RayTracer::A_Primitive::getPosition() {
    return position;
}

void RayTracer::A_Primitive::setPosition(Point3D pos) {
    position = pos;
}

Point3D RayTracer::A_Primitive::getRotation() {
    return rotation;
}

void RayTracer::A_Primitive::setRotation(Point3D rot) {
    rotation = rot;
}

Point3D RayTracer::A_Primitive::getScale() {
    return scale;
}

void RayTracer::A_Primitive::setScale(Point3D scale) {
    this->scale = scale;
}

A_Primitive::PrimitiveError::PrimitiveError(const std::string &message)
: message("PrimitiveError: " + message) {}
}  // namespace RayTracer
