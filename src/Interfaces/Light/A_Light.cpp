#include <string>
#include <memory>
#include <vector>

#include "Interfaces/Light/A_Light.hpp"

std::shared_ptr<RayTracer::I_Primitive> RayTracer::A_Lights::getParent() {
    return parent;
}

void RayTracer::A_Lights::setParent(std::shared_ptr<I_Primitive> parent) {
    this->parent = parent;
}

std::vector<std::shared_ptr<RayTracer::I_Primitive>>
&RayTracer::A_Lights::getChildrens() {
    return childrens;
}

void RayTracer::A_Lights::AddChildren(std::shared_ptr<I_Primitive> child) {
    childrens.push_back(child);
}

std::shared_ptr<RayTracer::I_Material> RayTracer::A_Lights::getMaterial() {
    return material;
}

void RayTracer::A_Lights::setMaterial(std::shared_ptr<I_Material> material) {
    this->material = material;
}

RayTracer::Point3D RayTracer::A_Lights::getPosition() {
    return position;
}

RayTracer::Point3D RayTracer::A_Lights::getRotation() {
    return rotation;
}

RayTracer::Point3D RayTracer::A_Lights::getScale() {
    return scale;
}

float RayTracer::A_Lights::getLuminescence(float distance, float angle) {
    (void) angle;
    return intensity / distance;
}

float RayTracer::A_Lights::getIntensity() {
    return intensity;
}

float RayTracer::A_Lights::getAngle() {
    return angle;
}

RayTracer::A_Lights::LightError::LightError(const std::string &message)
    : message("A_Lights" + message) {}
